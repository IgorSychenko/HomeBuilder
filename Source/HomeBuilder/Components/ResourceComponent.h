// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HomeBuilder/Interfaces/ResourceComponentSupport.h"
#include "ResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEBUILDER_API UResourceComponent
	: public UActorComponent
	, public IResourceComponentSupport
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	int32 CurrentResource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ResourceComponent|Resource")
	int32 MaxResource = 100;

public:	

	// IResourceComponentSupport Begin
	virtual int32 GetCurrentResource_Implementation() const override;
	virtual int32 GetMaxResource_Implementation() const override;
	virtual float GetRatio_Implementation() const override;
	virtual void ChangeCurrentResource_Implementation(int32 Change) override;
	// IResourceComponentSupport End
		
};
