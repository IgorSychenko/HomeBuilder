// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEBUILDER_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct", meta = (ClampMin = "0", UIMin = "0"))
	float ProgressCompleteTime = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent|Construct")
	TSubclassOf<AActor> ConstructActorClass;

	UFUNCTION()
	void CreateConstruct();

private:
	float Progress = 0.0f;

	bool bIsInProgress = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "BuildingComponent|Construct")
	void StartConstruct();
	
	UFUNCTION(BlueprintCallable, Category = "BuildingComponent|Construct")
	void StopConstruct();

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
	FORCEINLINE float GetProgress() const { return Progress; }

	UFUNCTION(BlueprintPure, Category = "BuildingComponent|Construct")
    FORCEINLINE bool IsInProgress() const { return bIsInProgress; }
		
};
