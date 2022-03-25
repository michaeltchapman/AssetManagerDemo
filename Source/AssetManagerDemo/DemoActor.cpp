//


#include "DemoActor.h"

#include "Engine/AssetManager.h"


// Sets default values
ADemoActor::ADemoActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADemoActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADemoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADemoActor::AsyncLoadBundle()
{
	UE_LOG(LogTemp, Verbose, TEXT("Load Primary Asset Bundles"));
	PrintDataAssetState();
	UAssetManager &Manager = UAssetManager::Get();
	TArray<FName> Bundles { Bundle };
	Manager.LoadPrimaryAsset(PrimaryAssetId, Bundles, FStreamableDelegate::CreateUObject(this, &ADemoActor::PrintDataAssetState));
}

void ADemoActor::UnloadPrimaryAsset()
{
	UE_LOG(LogTemp, Verbose, TEXT("Unload Primary Asset"));
	PrintDataAssetState();
	UAssetManager &Manager = UAssetManager::Get();
	Manager.UnloadPrimaryAsset(PrimaryAssetId);
	GEngine->ForceGarbageCollection(true);
	PrintDataAssetState();

}

void ADemoActor::LoadPrimaryAssetObject()
{
	UE_LOG(LogTemp, Verbose, TEXT("Load Primary Asset Object"));
	PrintDataAssetState();


	UAssetManager &Manager = UAssetManager::Get();
	auto Path = Manager.GetPrimaryAssetPath(PrimaryAssetId);

	FSoftObjectPtr Ptr(Path);
	UObject *Obj = Ptr.LoadSynchronous();
	if (!Obj)
		UE_LOG(LogTemp, Error, TEXT("Failed to load primary object %s using path %s"), *PrimaryAssetId.ToString(), *Path.ToString());

	PrintDataAssetState();
}

void ADemoActor::UnloadPrimaryAssetObject()
{
	UE_LOG(LogTemp, Verbose, TEXT("Unload Primary Asset Object"));
	PrintDataAssetState();
	UAssetManager &Manager = UAssetManager::Get();
	auto Path = Manager.GetPrimaryAssetPath(PrimaryAssetId);

	FStreamableManager StreamManager;
	StreamManager.Unload(Path);
	PrintDataAssetState();
}

void ADemoActor::PrintDataAssetState()
{
	UAssetManager &Manager = UAssetManager::Get();
	auto Path = Manager.GetPrimaryAssetPath(PrimaryAssetId);
	FSoftObjectPtr Ptr(Path);
	if (Ptr.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("Loaded: Primary Asset object %s"), *PrimaryAssetId.ToString())
	else
		UE_LOG(LogTemp, Error, TEXT("Not Loaded: Primary Asset object %s"), *PrimaryAssetId.ToString())

	TArray<FAssetBundleEntry> Entries;
	Manager.GetAssetBundleEntries(PrimaryAssetId, Entries);
	for (auto &Entry : Entries)
	{
		for (auto &Asset : Entry.BundleAssets)
		{
			FSoftObjectPtr AssetPtr(Asset);
			if (AssetPtr.IsValid())
				UE_LOG(LogTemp, Warning, TEXT("Loaded: Asset %s in bundle %s"), *Asset.ToString(), *Bundle.ToString())
			else
				UE_LOG(LogTemp, Error, TEXT("Not Loaded: Asset %s in bundle %s"), *Asset.ToString(), *Bundle.ToString())
		}
	}
}

