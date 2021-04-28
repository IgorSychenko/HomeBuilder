// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "BuildingGhostComponent.generated.h"


class AHomeGhost;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEBUILDER_API UBuildingGhostComponent : public UChildActorComponent
{
	GENERATED_BODY()

	friend AHomeGhost;

public:	
	// Sets default values for this component's properties
	UBuildingGhostComponent();

	UFUNCTION(BlueprintPure, Category="BuildingGhostComponent")
	FORCEINLINE AHomeGhost* GetHomeGhost() const { return HomeGhost; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateHomeGhost();

private:
	UPROPERTY()
	AHomeGhost* HomeGhost;
	
};
