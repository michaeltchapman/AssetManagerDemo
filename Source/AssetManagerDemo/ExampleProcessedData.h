//

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/AssetManagerTypes.h"
#include "ExampleProcessedData.generated.h"

/**
 * An example of a primary data asset child class that optionally does some processing
 * after bundles are parsed, then updates Asset Manager with custom bundle info and custom cook rules
 */
UCLASS()
class ASSETMANAGERDEMO_API UExampleProcessedData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UExampleProcessedData();
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	virtual void ProcessData();


#if WITH_EDITORONLY_DATA
	// This gets called during PostLoad and will wipe our customised bundles if left as default
	virtual void UpdateAssetBundleData() override {};
#endif

	UFUNCTION(BlueprintCallable, Category = "Example Data Asset")
	const TMap<FSoftObjectPath, FGameplayTagContainer> &GetCustomAssets() const { return TaggedCustomAssets; };

	UFUNCTION(BlueprintCallable, Category = "Example Data Asset")
	static TArray<FSoftObjectPath> GetAssetsInBundle(FPrimaryAssetId PrimaryAssetId, FName BundleName);
protected:
	/** Management rules for this specific asset, if set it will override the type rules */
	UPROPERTY(EditAnywhere, Category = "Data Asset Cook Rules", meta = (ShowOnlyInnerProperties))
	FPrimaryAssetRules Rules;

	UPROPERTY(EditAnywhere, Category = "Custom Processing")
	FName CustomAssetBundle;

	UPROPERTY(EditAnywhere, Category = "Custom Processing")
	FName CustomAssetBaseDirectory;

	UPROPERTY(EditAnywhere, Category = "Custom Processing")
	bool bCustomAssetRecurseDirectory;

	UPROPERTY(EditAnywhere, Category = "Custom Processing")
	FString InterfaceAssetMatchRegex;

	UPROPERTY(VisibleDefaultsOnly, Category = "Custom Processing")
	TMap<FSoftObjectPath, FGameplayTagContainer> TaggedCustomAssets;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "Custom Processing")
	TArray<FSoftObjectPath> DebugCustomAssets;
#endif
};
