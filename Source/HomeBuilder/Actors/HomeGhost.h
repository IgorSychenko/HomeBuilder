// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "HomeGhost.generated.h"

UCLASS()
class HOMEBUILDER_API AHomeGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomeGhost();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct")
	UBoxComponent* BoxCollision;

	UPROPERTY()
	TArray<AActor*> CollisionActors;

	UFUNCTION() 
	void OnCollisionOverlapBegin(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit);

	UFUNCTION() 
	void OnCollisionOverlapEnd(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex);

	UFUNCTION()
	void UpdateMaterial();

};
