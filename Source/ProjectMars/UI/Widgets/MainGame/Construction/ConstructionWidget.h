// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConstructionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UConstructionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UConstructionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MilitaryTab{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* HealthTab{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Resources{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Government{ nullptr };

	/*UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UConstructionButtonWidget* ConstructionButtonWidget{ nullptr };*/

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UConstructionListWidget* ConstructionListWidget{ nullptr };
};
