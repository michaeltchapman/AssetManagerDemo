//

#pragma once

#include "CoreMinimal.h"
#include "ExampleStaticData.h"
#include "UObject/Interface.h"
#include "DataAssetConsumer.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDataAssetConsumer : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Interface for assets that can consume a multi purpose Data Asset. This is the model outlined by MAllar
 *	where there might be a single Data Asset for an item that contains both a static mesh for use by a player
 *	holding the item and a texture for use by a shop that sells the item. Both the player class and the shop class
 *	can consume the data asset using this interface, avoiding the need to create multiple individual blueprints for every
 *	item. Instead there will be two base classes implementing IDataAssetConsumer that consume the asset in different
 *	ways, and a many UExampleProcessedData assets for the different items.
 */
class ASSETMANAGERDEMO_API IDataAssetConsumer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ConsumeAsset(UExampleStaticData *StaticDataAsset);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ConsumeAssetId(FPrimaryAssetId AssetId);
};
