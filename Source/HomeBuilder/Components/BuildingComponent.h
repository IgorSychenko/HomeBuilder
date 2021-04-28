// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class UBuildingGhostComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartConstruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndConstruct);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEBUILDER_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingComponent();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct", meta = (ClampMin = "0", UIMin = "0"))
	float ProgressCompleteTime = 4.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct", meta = (ClampMin = "0", UIMin = "0"))
	float OffsetConstructPosition = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct", meta = (ClampMin = "0", UIMin = "0"))
	int32 ConstructCost = 10;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct")
	TSubclassOf<AActor> ConstructActorClass;

	UFUNCTION()
	void CreateConstruct();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FVector GetRelativeLocation() const;
	
	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FVector GetSpawnLocation() const;

	UFUNCTION(BlueprintCallable, Category = "BuildingComponent|Construct")
	void StartConstruct();
	
	UFUNCTION(BlueprintCallable, Category = "BuildingComponent|Construct")
	void StopConstruct();

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FORCEINLINE float GetProgress() const { return Progress; }

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FORCEINLINE float GetProgressRatio() const { return ProgressCompleteTime > 0 ? static_cast<float>(Progress) / static_cast<float>(ProgressCompleteTime) : 1.f; }

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FORCEINLINE bool IsInProgress() const { return bIsInProgress; }

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FORCEINLINE int32 GetConstructCost() const { return ConstructCost; }

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	bool CanStartConstruct() const;

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	bool IsPositionValid() const;

	UPROPERTY(BlueprintAssignable, Category = "ResourceComponent|Resource")
	FStartConstruct OnStartConstruct;

	UPROPERTY(BlueprintAssignable, Category = "ResourceComponent|Resource")
	FEndConstruct OnEndConstruct;


private:
	float Progress = 0.0f;

	bool bIsInProgress = false;
	
	UPROPERTY()
	UBuildingGhostComponent* BuildingGhostComponent;
		
};
