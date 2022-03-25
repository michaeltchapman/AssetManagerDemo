//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoActor.generated.h"

UCLASS(Blueprintable)
class ASSETMANAGERDEMO_API ADemoActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Asset Manager Demo")
	void AsyncLoadBundle();

	UFUNCTION(BlueprintCallable, Category = "Asset Manager Demo")
	void PrintDataAssetState();

	UFUNCTION(BlueprintCallable, Category = "Asset Manager Demo")
	void LoadPrimaryAssetObject();
	UFUNCTION(BlueprintCallable, Category = "Asset Manager Demo")
	void UnloadPrimaryAssetObject();
	UFUNCTION(BlueprintCallable, Category = "Asset Manager Demo")
	void UnloadPrimaryAsset();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Asset Manager Demo")
	FPrimaryAssetId PrimaryAssetId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Asset Manager Demo")
	FName Bundle;
};
