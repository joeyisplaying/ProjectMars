// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConstructionButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UConstructionButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UConstructionButtonWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	void OnButtonClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainButton{ nullptr };

private:

};
