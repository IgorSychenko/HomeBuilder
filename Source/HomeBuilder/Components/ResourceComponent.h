// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResourceChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEBUILDER_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	int32 CurrentResource = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ResourceComponent|Resource")
	int32 MaxResource = 100;

	public:
	UFUNCTION(BlueprintPure, Category = "ResourceComponent|Resource")
	FORCEINLINE int32 GetCurrentResource() const { return CurrentResource; }
	
	UFUNCTION(BlueprintPure, Category = "ResourceComponent|Resource")
	FORCEINLINE int32 GetMaxResource() const { return MaxResource; }
	
	UFUNCTION(BlueprintPure, Category = "ResourceComponent|Resource")
	FORCEINLINE float GetRatio() const { return static_cast<float>(CurrentResource) / static_cast<float>(MaxResource); }
	
	UFUNCTION(BlueprintCallable, Category = "ResourceComponent|Resource")
	void ChangeCurrentResource(int32 Change);

	UPROPERTY(BlueprintAssignable, Category = "ResourceComponent|Resource")
	FResourceChange OnResourceChange;
		
};
