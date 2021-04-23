// Copyright Epic Games, Inc. All Rights Reserved.

#include "HomeBuilderGameMode.h"
#include "HomeBuilderCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHomeBuilderGameMode::AHomeBuilderGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
