// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingComponent.h"

#include "BuildingGhostComponent.h"
#include "ResourceComponent.h"
#include "HomeBuilder/Actors/HomeGhost.h"
#include "HomeBuilder/Interfaces/ResourceComponentSupport.h"
#include "HomeBuilder/Player/HomeBuilderCharacter.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	BuildingGhostComponent = IBuildingComponentSupport::Execute_GetBuildingGhostComponent(GetOwner());
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

FVector UBuildingComponent::GetRelativeLocation() const
{
	return GetSpawnLocation() - GetOwner()->GetActorLocation();
}

FVector UBuildingComponent::GetSpawnLocation() const
{
	FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * OffsetConstructPosition;
	FHitResult OutHit;
	const FVector Start = SpawnLocation;
	const FVector End = Start + FVector(0.0f, 0.0f, -1000.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(IBuildingComponentSupport::Execute_GetBuildingGhostComponent(GetOwner())->GetHomeGhost());

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn, Params))
	{
		SpawnLocation = OutHit.Location;
	}

	return SpawnLocation;
}

void UBuildingComponent::StartConstruct()
{
	if (!ConstructActorClass) return;
	if (IsInProgress()) return;
	if (!CanStartConstruct()) return;

	if (const auto ResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(GetOwner()))
	{
		ResourceComponent->ChangeCurrentResource(-GetConstructCost());

		bIsInProgress = true;

		OnStartConstruct.Broadcast();
	}
}

void UBuildingComponent::StopConstruct()
{
	if (IsInProgress())
	{
		bIsInProgress = false;
		
		Progress = 0.0f;

		OnEndConstruct.Broadcast();
	}
}

bool UBuildingComponent::IsPositionValid() const
{
	if (!BuildingGhostComponent) return true;

	return BuildingGhostComponent->GetHomeGhost()->CollisionActors.Num() == 0;
}

bool UBuildingComponent::CanStartConstruct() const
{
	if (!IsPositionValid()) return false;
	
	if (const auto ResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(GetOwner()))
	{
		return ResourceComponent->GetCurrentResource() >= GetConstructCost();		
	}
	
	return false;
}

void UBuildingComponent::CreateConstruct()
{
	StopConstruct();

	if (ConstructActorClass)
	{		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FVector SpawnLocation = GetSpawnLocation();
		
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