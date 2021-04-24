// Fill out your copyright notice in the Description page of Project Settings.


#include "Home.h"
#include "HomeBuilder/Components/ResourceComponentProduction.h"
#include "Components/WidgetComponent.h"
#include "HomeBuilder/UI/ResourceWidget.h"

// Sets default values
AHome::AHome()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	ResourceComponentProduction = CreateDefaultSubobject<UResourceComponentProduction>(TEXT("ResourceComponentProduction"));
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetResource"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetClass(UResourceWidget::StaticClass());
	
}

// Called when the game starts or when spawned
void AHome::BeginPlay()
{
	Super::BeginPlay();

	if (auto ResourceWidget = Cast<UResourceWidget>(WidgetComponent->GetUserWidgetObject()))
	{
		ResourceWidget->Init(this);
	}
}

UResourceComponent* AHome::GetResourceComponent_Implementation() const
{
	return Cast<UResourceComponent>(ResourceComponentProduction);
}