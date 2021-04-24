// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UResourceComponent::ChangeCurrentResource(int32 Change)
{
	CurrentResource = FMath::Clamp(CurrentResource + Change, 0, MaxResource);

	OnResourceChange.Broadcast();
}