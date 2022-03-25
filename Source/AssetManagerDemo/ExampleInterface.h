//

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ExampleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UExampleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ASSETMANAGERDEMO_API IExampleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	FGameplayTagContainer GetTagContainer();
};
