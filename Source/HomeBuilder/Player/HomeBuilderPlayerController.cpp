// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeBuilderPlayerController.h"

void AHomeBuilderPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}