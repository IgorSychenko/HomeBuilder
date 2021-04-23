// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingComponent.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsInProgress())
	{
		Progress += DeltaTime;

		if (Progress >= ProgressCompleteTime)
		{
			CreateConstruct();
		}
	}
}

void UBuildingComponent::StartConstruct()
{
	if (!ConstructActorClass) return;
	
	if (!IsInProgress())
	{
		bIsInProgress = true;
	}
}

void UBuildingComponent::StopConstruct()
{
	if (IsInProgress())
	{
		bIsInProgress = false;
		Progress = 0.0f;
	}
}

void UBuildingComponent::CreateConstruct()
{
	StopConstruct();

	if (ConstructActorClass)
	{		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FVector SpawnLocation = GetOwner()->GetActorLocation();
		const FRotator SpawnRotation = GetOwner()->GetActorRotation();
		
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(ConstructActorClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (NewActor)
		{
			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UBuildingComponent::CreateConstruct. Error actor creating!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingComponent::CreateConstruct. ConstructActorClass is null!"));
	}
}