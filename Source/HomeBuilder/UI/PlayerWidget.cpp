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

			IBuildingComponentSupport::Execute_GetBuildingComponent(Character)->OnStartConstruct.AddDynamic(this, &UPlayerWidget::UpdateWidget);

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
		
		if (Character->CanTakeResource())
		{
			TakeResource->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			TakeResource->SetVisibility(ESlateVisibility::Hidden);
		}

		if (IBuildingComponentSupport::Execute_GetBuildingComponent(Character)->CanStartConstruct())
		{
			ConstructHome->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ConstructHome->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPlayerWidget::OnTakeResourceClicked()
{
	Character->TakeResource();
}

void UPlayerWidget::OnConstructHomeClicked()
{
	IBuildingComponentSupport::Execute_GetBuildingComponent(Character)->StartConstruct();
}