// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGhost.h"

#include "HomeBuilder/Components/BuildingGhostComponent.h"

// Sets default values
AHomeGhost::AHomeGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

void AHomeGhost::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHomeGhost::OnCollisionOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AHomeGhost::OnCollisionOverlapEnd);
}

void AHomeGhost::OnCollisionOverlapBegin(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	CollisionActors.AddUnique(OtherActor);
	UpdateMaterial();
}

void AHomeGhost::OnCollisionOverlapEnd(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex)
{
	CollisionActors.Remove(OtherActor);
	UpdateMaterial();
}

void AHomeGhost::UpdateMaterial()
{
	UE_LOG(LogTemp, Warning, TEXT("AHomeGhost::UpdateMaterial!"));
	
	if (auto BuildingGhostComponent = Cast<UBuildingGhostComponent>(GetParentComponent()))
	{
		BuildingGhostComponent->UpdateHomeGhost();
	}
}