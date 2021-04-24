// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

class UResourceComponent;

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

	UFUNCTION(BlueprintCallable, Category = "ResourceWidget|ResourceComponent")
	void UpdateWidget();

protected:
	UPROPERTY (meta = (BindWidget))
	class UProgressBar* ResourceBar;

	UPROPERTY (meta = (BindWidget))
	class UTextBlock* ResourceText;

private:
	UPROPERTY()
	UResourceComponent* OwnerResourceComponent;
	
};
