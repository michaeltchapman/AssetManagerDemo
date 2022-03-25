//

#pragma once

#include "CoreMinimal.h"
#include "DataAssetConsumer.h"
#include "GameFramework/Actor.h"
#include "MeshConsumer.generated.h"

UCLASS(Blueprintable)
class ASSETMANAGERDEMO_API AMeshConsumer : public AActor, public IDataAssetConsumer
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeshConsumer();
	virtual void ConsumeAsset_Implementation(UExampleStaticData* DataAsset) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
};
