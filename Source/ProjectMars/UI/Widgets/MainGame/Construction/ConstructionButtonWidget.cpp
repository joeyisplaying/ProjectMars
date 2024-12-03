// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionButtonWidget.h"

#include "Components/Button.h"
#include "Logging/StructuredLog.h"

UConstructionButtonWidget::UConstructionButtonWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UConstructionButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UConstructionButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UConstructionButtonWidget::OnButtonClicked()
{
	UE_LOGFMT(LogTemp, Warning, "Construction Button Clicked");
}
