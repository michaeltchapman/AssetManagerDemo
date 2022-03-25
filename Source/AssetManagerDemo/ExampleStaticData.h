//

#pragma once

#include "CoreMinimal.h"
#include "ExampleStaticData.generated.h"

/**
 * An example of a Data Asset that has its data defined statically in two variables. This can be used with a consumption
 * interface so that different classes can consume this data in different ways
 */
UCLASS(BlueprintType)
class ASSETMANAGERDEMO_API UExampleStaticData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Example Static Data")
	UStaticMesh* GetMesh() const;
	UFUNCTION(BlueprintCallable, Category = "Example Static Data")
	UTexture2D* GetTexture() const;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display, AssetRegistrySearchable, meta = (AssetBundles = "MyBundle"))
	TSoftObjectPtr<UStaticMesh> MeshPtr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display, AssetRegistrySearchable, meta = (AssetBundles = "MyBundle"))
	TSoftObjectPtr<UTexture2D> TexturePtr;
};
