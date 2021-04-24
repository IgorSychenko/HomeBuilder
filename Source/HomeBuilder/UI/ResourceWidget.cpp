// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HomeBuilder/Components/ResourceComponent.h"
#include "HomeBuilder/Interfaces/ResourceComponentSupport.h"

UResourceWidget::UResourceWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void UResourceWidget::Init(AActor* Owner)
{
	if (Owner->GetClass()->ImplementsInterface(UResourceComponentSupport::StaticClass()))
	{
		OwnerResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(Owner);

		if (OwnerResourceComponent)
		{
			OwnerResourceComponent->OnResourceChange.AddDynamic(this, &UResourceWidget::UpdateWidget);			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UResourceWidget::Init. OwnerResourceComponent is null!"));
		}

		UpdateWidget();
	}
}

void UResourceWidget::UpdateWidget()
{
	if (OwnerResourceComponent)
	{
		ResourceBar->SetPercent(OwnerResourceComponent->GetRatio());
		
		const FString ResourceString = FString::Printf(TEXT("%i/%i"), OwnerResourceComponent->GetCurrentResource(), OwnerResourceComponent->GetMaxResource());
		ResourceText->SetText(FText::FromString(ResourceString));
	}
}
