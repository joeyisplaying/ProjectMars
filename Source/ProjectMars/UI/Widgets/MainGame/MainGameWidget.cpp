// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameWidget.h"

#include "Components/Button.h"
#include "Construction/ConstructionButtonWidget.h"
#include "Construction/ConstructionWidget.h"
#include "Logging/StructuredLog.h"
#include "ProjectMars/Civic/Settlement.h"
#include "ProjectMars/Delegates/DelegateController.h"

UMainGameWidget::UMainGameWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsConstructionOpen = false;
}

void UMainGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainGameWidget::PostInitProperties()
{
	Super::PostInitProperties();
}

void UMainGameWidget::ShowConstruction()
{
	if (bIsConstructionOpen)
	{
		this->ConstructionWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsConstructionOpen = false;
	} else
	{
		this->ConstructionWidget->SetVisibility(ESlateVisibility::Visible);
		bIsConstructionOpen = true;
	}
}

void UMainGameWidget::ShowConstructionButton(const ASettlement* Settlement)
{
	UE_LOGFMT(LogTemp, Display, "SHOWING CONSTRUCTION BUTTON");
	this->ConstructionButtonWidget->SetVisibility(ESlateVisibility::Visible);
}

UMainGameWidget* UMainGameWidget::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	DelegateController = DelegateControllerVar;
	return this;
}

UDelegateController* UMainGameWidget::GetDelegateController()
{
	return DelegateController;
}

void UMainGameWidget::InitialiseEvents()
{
	ensure(DelegateController);
	
	this->ConstructionButtonWidget->AddToViewport();
	this->ConstructionButtonWidget->SetVisibility(ESlateVisibility::Hidden);
	this->ConstructionWidget->AddToViewport();
	this->ConstructionWidget->SetVisibility(ESlateVisibility::Hidden);
	
	DelegateController->OnSettlementClick.AddDynamic(this, &UMainGameWidget::ShowConstructionButton);
	this->ConstructionButtonWidget->MainButton->OnClicked.AddDynamic(this, &UMainGameWidget::ShowConstruction);
}


