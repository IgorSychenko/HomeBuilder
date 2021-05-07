// Copyright Epic Games, Inc. All Rights Reserved.

#include "HomeBuilderGameMode.h"
#include "HomeBuilder/Player/HomeBuilderCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AHomeBuilderGameMode::AHomeBuilderGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/HomeBuilder/Blueprints/Player/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}