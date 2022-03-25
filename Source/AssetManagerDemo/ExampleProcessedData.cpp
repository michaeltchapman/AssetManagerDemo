//

#include "ExampleProcessedData.h"

#include "ExampleInterface.h"
#include "Engine/AssetManager.h"
#include "UObject/ObjectSaveContext.h"

UExampleProcessedData::UExampleProcessedData()
	: Super()
{
	Rules.bApplyRecursively = false;
	Rules.Priority = 0;
}

void UExampleProcessedData::PreSave(FObjectPreSaveContext ObjectPreSaveContext)
{
	Super::PreSave(ObjectPreSaveContext);
	// By default parse the metadata of bundles
	if (UAssetManager::IsValid())
	{
		AssetBundleData.Reset();
		UAssetManager::Get().InitializeAssetBundlesFromMetadata(this, AssetBundleData);

		// Do custom data processing
		ProcessData();

		if (UAssetManager::IsValid())
		{
			// Bundles may have changed, refresh
			UAssetManager::Get().RefreshAssetData(this);
		}

		// Update asset rules
		FPrimaryAssetId PrimaryAssetId = GetPrimaryAssetId();
		UAssetManager::Get().SetPrimaryAssetRules(PrimaryAssetId, Rules);
	}
}

void UExampleProcessedData::ProcessData()
{
	TaggedCustomAssets.Reset();

#if WITH_EDITORONLY_DATA
	DebugCustomAssets.Reset();
#endif

	UAssetManager& Manager = UAssetManager::Get();
	IAssetRegistry& AssetRegistry = Manager.GetAssetRegistry();

	FARFilter RegistryFilter;
	RegistryFilter.PackagePaths.Add(CustomAssetBaseDirectory);
	RegistryFilter.bRecursivePaths = bCustomAssetRecurseDirectory;

	TArray<FAssetData> RegistryAssets;
	//AssetRegistry.GetAssetsByPath(PackagePath, RegistryAssets, true);
	AssetRegistry.GetAssets(RegistryFilter, RegistryAssets);

	TArray<FSoftObjectPath> NewPaths;

	FRegexPattern Regex = FRegexPattern(InterfaceAssetMatchRegex);

	for (const FAssetData& AssetData : RegistryAssets)
	{
		FSoftObjectPath AssetRef = Manager.GetAssetPathForData(AssetData);

		if (!AssetRef.IsNull())
		{
			NewPaths.Add(AssetRef);

			// When we load a transition, we want to try to get its connection class using the TransitionConnection interface
			// this will cause hitches when saving the data asset
			FRegexMatcher Matcher(Regex, AssetData.ObjectPath.ToString());
			if (!InterfaceAssetMatchRegex.IsEmpty() && Matcher.FindNext())
			{
				UObject* AssetObj = AssetRef.TryLoad();
				UBlueprintGeneratedClass* AssetBP = Cast<UBlueprintGeneratedClass>(AssetObj);
				if (AssetBP)
				{
					auto CDO = AssetBP->GetDefaultObject<AActor>();
					if (CDO && CDO->Implements<UExampleInterface>())
					{
						FGameplayTagContainer Tags = IExampleInterface::Execute_GetTagContainer(CDO);
						if (!Tags.IsEmpty())
						{
							TaggedCustomAssets.Add(AssetRef, Tags);
						}
					}
				}
			}
		}
	}

#if WITH_EDITORONLY_DATA
	DebugCustomAssets.Append(NewPaths);
#endif

	AssetBundleData.SetBundleAssets(CustomAssetBundle, MoveTemp(NewPaths));
}

TArray<FSoftObjectPath> UExampleProcessedData::GetAssetsInBundle(FPrimaryAssetId PrimaryAssetId, FName BundleName)
{
	UAssetManager &Manager = UAssetManager::Get();
	FAssetBundleEntry BundleEntry = Manager.GetAssetBundleEntry(PrimaryAssetId, BundleName);
	return BundleEntry.BundleAssets;
}
