// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UResourceComponent::GetCurrentResource_Implementation() const
{
	return CurrentResource;
}

int32 UResourceComponent::GetMaxResource_Implementation() const
{
	return MaxResource;
}

float UResourceComponent::GetRatio_Implementation() const
{
	return static_cast<float>(CurrentResource) / static_cast<float>(MaxResource);
}

void UResourceComponent::ChangeCurrentResource_Implementation(int32 Change)
{
	CurrentResource = FMath::Clamp(CurrentResource + Change, 0, MaxResource);
}