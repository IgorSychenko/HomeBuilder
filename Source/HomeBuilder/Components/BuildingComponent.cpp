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

		// Find location
		FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * OffsetConstructPosition;
		FHitResult OutHit;
		const FVector Start = SpawnLocation;
		const FVector End = Start + FVector(0.0f, 0.0f, -1000.0f);

		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn, FCollisionQueryParams()))
		{
			SpawnLocation = OutHit.Location;
		}
		
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(ConstructActorClass, SpawnLocation, GetOwner()->GetActorRotation(), SpawnParams);
		if (!NewActor)
		{
			UE_LOG(LogTemp, Error, TEXT("UBuildingComponent::CreateConstruct. Error actor creating!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingComponent::CreateConstruct. ConstructActorClass is null!"));
	}
}