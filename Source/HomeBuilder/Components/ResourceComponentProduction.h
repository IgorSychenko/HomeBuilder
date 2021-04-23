// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceComponent.h"
#include "ResourceComponentProduction.generated.h"

/**
 * 
 */
UCLASS()
class HOMEBUILDER_API UResourceComponentProduction : public UResourceComponent
{
	GENERATED_BODY()

public:
	UResourceComponentProduction();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ResourceComponent|Resource", meta = (ClampMin = "0", UIMin = "0"))
	int32 ResourceChangePerTick = 1;
	
};
