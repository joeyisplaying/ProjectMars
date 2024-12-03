// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConstructionListWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UConstructionListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UConstructionListWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BuildingButton0{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BuildingButton1{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BuildingButton2{ nullptr };
};
