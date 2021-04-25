// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HomeBuilder/Components/BuildingComponent.h"
#include "HomeBuilder/Components/ResourceComponent.h"
#include "HomeBuilder/Player/HomeBuilderCharacter.h"

bool UPlayerWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (GetOwningPlayer())
		{
			Character = Cast<AHomeBuilderCharacter>(GetOwningPlayer()->GetCharacter());
			auto OwnerResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(Character);
			OwnerResourceComponent->OnResourceChange.AddDynamic(this, &UPlayerWidget::UpdateWidget);

			Character->GetBuildingComponent()->OnStartConstruct.AddDynamic(this, &UPlayerWidget::UpdateWidget);

			Character->OnContactArrayChanged.AddDynamic(this, &UPlayerWidget::UpdateWidget);
			
			TakeResource->OnClicked.AddDynamic(this, &UPlayerWidget::OnTakeResourceClicked);
			
			ConstructHome->OnClicked.AddDynamic(this, &UPlayerWidget::OnConstructHomeClicked);

			UpdateWidget();
		}

		return true;
	}

	return false;
}

void UPlayerWidget::UpdateWidget()
{
	if (Character)
	{
		const auto OwnerResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(Character);
		ResourceBar->SetPercent(OwnerResourceComponent->GetRatio());
		
		const FString ResourceString = FString::Printf(TEXT("%i/%i"), OwnerResourceComponent->GetCurrentResource(), OwnerResourceComponent->GetMaxResource());
		ResourceText->SetText(FText::FromString(ResourceString));

		bool bShowMouse = false;
		if (Character->CanTakeResource())
		{
			TakeResource->SetVisibility(ESlateVisibility::Visible);

			bShowMouse = true;
		}
		else
		{
			TakeResource->SetVisibility(ESlateVisibility::Hidden);
		}

		if (Character->GetBuildingComponent()->CanStartConstruct())
		{
			ConstructHome->SetVisibility(ESlateVisibility::Visible);

			bShowMouse = true;
		}
		else
		{
			ConstructHome->SetVisibility(ESlateVisibility::Hidden);
		}

		if (Character->CanTakeResource() || Character->GetBuildingComponent()->CanStartConstruct())
		{
			bShowMouse = true;
		}

		GetOwningPlayer()->bShowMouseCursor = bShowMouse;
		GetOwningPlayer()->bEnableClickEvents = bShowMouse;
		GetOwningPlayer()->bEnableMouseOverEvents = bShowMouse;

		if (Character->GetBuildingComponent()->IsInProgress())
		{
			ConstructProgressText->SetText(FText::FromString(TEXT("Constructing...")));
			ConstructProgressText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ConstructProgressText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPlayerWidget::OnTakeResourceClicked()
{
	Character->TakeResource();
}

void UPlayerWidget::OnConstructHomeClicked()
{
	Character->GetBuildingComponent()->StartConstruct();
}