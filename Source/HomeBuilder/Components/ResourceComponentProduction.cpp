// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponentProduction.h"

UResourceComponentProduction::UResourceComponentProduction()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;
}

void UResourceComponentProduction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ChangeCurrentResource(ResourceChangePerTick);
}