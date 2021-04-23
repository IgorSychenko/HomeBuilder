// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Home.generated.h"

class UResourceComponentProduction;

UCLASS()
class HOMEBUILDER_API AHome : public AActor
{
	GENERATED_BODY()
	
public:
	AHome();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ResourceComponent")
	UResourceComponentProduction* ResourceComponentProduction;

};
