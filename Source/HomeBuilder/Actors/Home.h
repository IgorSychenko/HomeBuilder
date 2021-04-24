// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomeBuilder/Interfaces/ResourceComponentSupport.h"
#include "Home.generated.h"

class UResourceComponentProduction;
class UWidgetComponent;

UCLASS()
class HOMEBUILDER_API AHome
	: public AActor
	, public IResourceComponentSupport
{
	GENERATED_BODY()
	
public:
	AHome();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ResourceComponent")
	UResourceComponentProduction* ResourceComponentProduction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetComponent")
	UWidgetComponent* WidgetComponent;

	// IResourceComponentSupport Begin
	virtual UResourceComponent* GetResourceComponent_Implementation() const override;
	// IResourceComponentSupport End

};
