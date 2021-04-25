// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "PlayerWidget.generated.h"

class AHomeBuilderCharacter;
class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HOMEBUILDER_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "PlayerWidget")
	void UpdateWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ResourceBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResourceText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* TakeResource;

	UFUNCTION()
	void OnTakeResourceClicked();
	
	UPROPERTY(meta = (BindWidget))
	UButton* ConstructHome;

	UFUNCTION()
	void OnConstructHomeClicked();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConstructProgressText;

private:
	UPROPERTY()
	AHomeBuilderCharacter* Character;
	
};
