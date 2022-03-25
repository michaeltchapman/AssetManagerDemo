// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetManagerDemoGameMode.h"
#include "AssetManagerDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssetManagerDemoGameMode::AAssetManagerDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
