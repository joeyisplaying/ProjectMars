// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectMars/Economy/Data/EconomyData.h"
#include "BaseHUD.generated.h"

class UEconomyData;
class AArmy;

// Widgets
class UDevInfoWidget;
class UStartButtonWidget;
class UDelegateController;
class UPopulationController;
class ABasePlayerController;
class UMainMenuWidget;
class UChooseFactionWidget;
class UMainMenu2Widget;
class UMainGameWidget;
class UEventPopupWidget;

class UNation;
class UPopulationData;

UCLASS()
class PROJECTMARS_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABaseHUD();

	// Functions
	UFUNCTION()
	void DrawFactionInfo();
	
	void PopulateDataObjects();

	UFUNCTION()
	void DrawMainMenu();

	UFUNCTION()
	void AddToViewport(UUserWidget* Widget);

	UFUNCTION()
	void RemoveFromParent(UUserWidget* Widget);

	UFUNCTION()
	void RemoveMainMenuFromParent();

	UFUNCTION()
	void RemoveMainMenu2FromParent();

	UFUNCTION()
	void LoadMainWorld();

	// Getters

	// Setters
	UFUNCTION()
	ABaseHUD* SetNation(const UNation* NationVar);
	
	virtual void DrawHUD() override;

	UFUNCTION()
	void SetDateSuffix(const FString& SuffixVal);

	UFUNCTION()
	void InitialiseEconomyData(const UEconomyData* EconomyDataVar);

	UFUNCTION()
	static FVector2D GetMonitorResolution();

	UFUNCTION()
	static FVector2D GetViewportResolution();

	UFUNCTION()
	static FVector2D GetCenterOfScreen();
	
	UFUNCTION()
	FVector2D GetMousePosition2D() const;

	UFUNCTION()
	void DrawSelectionBox();

	UFUNCTION()
	void InitialisePointers();
	
	UFUNCTION()
	void DrawEconomyData(const UEconomyData* EconomyDataVar);
	
	UFUNCTION()
	void DrawTooltip();
	
	UFUNCTION()
	void GetActorsUnderSelectionBox();

	UFUNCTION()
	void DrawEventPopup();

	UFUNCTION()
	void MoveWidgetInViewportWithMouse(class UUserWidget* EventPopupWidgetToMove);

	UFUNCTION()
	UDevInfoWidget* GetDevInfoWidget() const;

	UFUNCTION()
	void BroadcastStartButton();

	UFUNCTION()
	void SubscribeToEvents();

	// Setters
	
	UFUNCTION()
	ABaseHUD* SetDelegateController(UDelegateController* DelegateControllerVar);

private:
	// Functions
	
	UFUNCTION()
	void UpdateSeasonText(const FString& NewSeasonVar);
	
	UFUNCTION()
	void DrawFPS();

	UFUNCTION()
	void DrawDevInfo();

	UFUNCTION()
	void SetYearText(const FString& CurrentDateVar);

	// Components
	UPROPERTY()
	const UNation* Nation{ nullptr };

	UPROPERTY()
	const UPopulationData* PopulationData{ nullptr };

	// Properties
	UPROPERTY()
	FString CurrentDate;
	
	UPROPERTY(EditAnywhere)
	UDelegateController* DelegateController{ nullptr };
	
	UPROPERTY(EditAnywhere)
	int32 FPSNum{};

	UPROPERTY(EditAnywhere)
	FString DateSuffix{};

	UPROPERTY(EditAnywhere)
	const UEconomyData* EconomyData{ nullptr };

	UPROPERTY(EditAnywhere)
	class AProjectMarsPlayer* Player{ nullptr };

	UPROPERTY(EditAnywhere)
	FVector2D InitialSelectionPoint{};
	
	UPROPERTY(EditAnywhere)
	FVector2D CurrentSelectionPoint{};
	
	UPROPERTY(EditAnywhere)
	bool bHasStartedSelecting;

	UPROPERTY(EditAnywhere, Category = "SelectionBox")
	FLinearColor SelectionBoxColor{};
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEconomyWidget> EconomyWidgetClass;
	
	UPROPERTY(EditAnywhere)
	FVector2D StartingEventPopupPosition = FVector2D(660, 115);

	UPROPERTY(EditAnywhere)
	AArmy* ArmySelected{ nullptr };

	UPROPERTY(EditAnywhere)
	TArray<class AArmy*> ArmiesUnderSelectionBox;

	UPROPERTY(EditAnywhere)
	FVector2D CurrentEventPopupPos;

	UPROPERTY(EditAnywhere)
	FVector2D DistanceBetweenMouseAndLeftSideOfWidget;

	// Widgets
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UEventPopupWidget> EventPopupWidgetClass;
	
	UPROPERTY(EditAnywhere)
	UEventPopupWidget* EventPopupWidget{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UMainGameWidget> MainGameWidgetClass;
	
	UPROPERTY(EditAnywhere)
	UMainGameWidget* MainGameWidget{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UMainMenu2Widget> MainMenu2WidgetClass;
	
	UPROPERTY(EditAnywhere)
	UMainMenu2Widget* MainMenu2Widget{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UChooseFactionWidget> ChooseFactionWidgetClass;

	UPROPERTY(EditAnywhere)
	UChooseFactionWidget* ChooseFactionWidget{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	UMainMenuWidget* MainMenuWidget{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UBaseGameplayWidget> BaseGameplayWidgetClass;

	UPROPERTY(EditAnywhere)
	class UBaseGameplayWidget* BaseGameplayWidget{ nullptr };

	UPROPERTY(EditAnywhere)
	class UEconomyWidget* EconomyWidget{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UDevInfoWidget> DevInfoWidgetClass;

	UPROPERTY(EditAnywhere)
	UDevInfoWidget* DevInfoWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UStartButtonWidget> StartButtonWidgetClass;

	UPROPERTY(EditAnywhere)
	UStartButtonWidget* StartButtonWidget{ nullptr };

	UPROPERTY(EditAnywhere)
	FString CurrentSeason;

	UPROPERTY(EditAnywhere)
	int32 CurrentYear;

protected:
	virtual void BeginPlay() override;
		
};