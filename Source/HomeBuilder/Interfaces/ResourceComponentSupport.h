// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResourceComponentSupport.generated.h"

class UResourceComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResourceComponentSupport : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOMEBUILDER_API IResourceComponentSupport
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "ResourceComponent")
	UResourceComponent* GetResourceComponent() const;
};
