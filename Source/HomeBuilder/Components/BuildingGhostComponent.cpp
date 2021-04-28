// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingGhostComponent.h"
#include "BuildingComponent.h"
#include "HomeBuilder/Actors/HomeGhost.h"
#include "HomeBuilder/Interfaces/BuildingComponentSupport.h"

// Sets default values for this component's properties
UBuildingGhostComponent::UBuildingGhostComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UBuildingGhostComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetOwner()->GetClass()->ImplementsInterface(UBuildingComponentSupport::StaticClass()))
	{
		const auto BuildingComponent = IBuildingComponentSupport::Execute_GetBuildingComponent(GetOwner());
		SetRelativeLocation(BuildingComponent->GetRelativeLocation());
		
		BuildingComponent->OnStartConstruct.AddDynamic(this, &UBuildingGhostComponent::UpdateHomeGhost);
		BuildingComponent->OnEndConstruct.AddDynamic(this, &UBuildingGhostComponent::UpdateHomeGhost);

		HomeGhost = Cast<AHomeGhost>(GetChildActor());
	}

	UpdateHomeGhost();	
}

void UBuildingGhostComponent::UpdateHomeGhost()
{
	UE_LOG(LogTemp, Warning, TEXT("UBuildingGhostComponent::UpdateMaterial!"));
	
	if (GetOwner()->GetClass()->ImplementsInterface(UBuildingComponentSupport::StaticClass()))
	{
		if (const auto BuildingComponent = IBuildingComponentSupport::Execute_GetBuildingComponent(GetOwner()))
		{
			SetVisibility(BuildingComponent->CanStartConstruct());
		}
	}
}