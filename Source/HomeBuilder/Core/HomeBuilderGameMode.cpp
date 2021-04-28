// Copyright Epic Games, Inc. All Rights Reserved.

#include "HomeBuilderGameMode.h"
#include "HomeBuilder/Player/HomeBuilderCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AHomeBuilderGameMode::AHomeBuilderGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/HomeBuilder/Blueprints/Player/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AHomeBuilderGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableMouseOverEvents = true;
}