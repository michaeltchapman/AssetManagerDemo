//

#pragma once

#include "CoreMinimal.h"
#include "DataAssetConsumer.h"
#include "UObject/Object.h"
#include "TextureConsumer.generated.h"

/**
 *
 */
UCLASS()
class ASSETMANAGERDEMO_API ATextureConsumer : public AActor, public IDataAssetConsumer
{
	GENERATED_BODY()

public:
	ATextureConsumer();
	virtual void ConsumeAsset_Implementation(UExampleStaticData* DataAsset) override;
protected:
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture Consumer")
	UMaterialInterface* Material;
};
