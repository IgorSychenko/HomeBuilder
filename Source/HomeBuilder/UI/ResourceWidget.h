// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

class UResourceComponent;
class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HOMEBUILDER_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UResourceWidget(const FObjectInitializer& ObjectInitializer);
	
	void Init(AActor* Owner);

	UFUNCTION(BlueprintPure, Category = "ResourceWidget|ResourceComponent")
	FORCEINLINE UResourceComponent* GetOwnerResourceComponent() const { return OwnerResourceComponent; }

	UFUNCTION(BlueprintCallable, Category = "ResourceWidget")
	void UpdateWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ResourceBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResourceText;

private:
	UPROPERTY()
	UResourceComponent* OwnerResourceComponent;
	
};
