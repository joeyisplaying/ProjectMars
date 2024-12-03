// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameWidget.generated.h"

class UDelegateController;
class UFactionStatsWidget;
class UMiniMapWidget;
class UFactionButtonWidget;
class UMainMenuButtonWidget;
class UDateWidget;
class ASettlement;

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UMainGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UMainGameWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	virtual void PostInitProperties() override;

	UFUNCTION()
	void ShowConstruction();

	UFUNCTION()
	void InitialiseEvents();

	UFUNCTION()
	void ShowConstructionButton(const ASettlement* Settlement);

	UFUNCTION()
	UMainGameWidget* SetDelegateController(UDelegateController* DelegateControllerVar);

	UFUNCTION()
	UDelegateController* GetDelegateController();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UConstructionButtonWidget* ConstructionButtonWidget{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UConstructionWidget* ConstructionWidget{ nullptr };
	
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UFactionStatsWidget* FactionStatsWidget{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMiniMapWidget* MiniMapWidget{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UFactionButtonWidget* FactionButtonWidget{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMainMenuButtonWidget* MainMenuButtonWidget{ nullptr };

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UDateWidget* DateWidget{ nullptr };

	UPROPERTY(EditAnywhere)
	UDelegateController* DelegateController{ nullptr };
	
	bool bIsConstructionOpen;
};
