// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HomeBuilderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOMEBUILDER_API AHomeBuilderPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
