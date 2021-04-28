// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeBuilderGameMode.generated.h"

UCLASS(minimalapi)
class AHomeBuilderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHomeBuilderGameMode();

	virtual void BeginPlay() override;
};



