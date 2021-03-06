// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingComponentSupport.generated.h"

class UBuildingGhostComponent;
class UBuildingComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuildingComponentSupport : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOMEBUILDER_API IBuildingComponentSupport
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "BuildingComponent")
	UBuildingComponent* GetBuildingComponent() const;
	
	UFUNCTION(BlueprintNativeEvent, Category = "BuildingComponent")
	UBuildingGhostComponent* GetBuildingGhostComponent() const;
};
