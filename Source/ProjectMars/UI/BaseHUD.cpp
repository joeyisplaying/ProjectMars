// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

#include "Engine.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Logging/StructuredLog.h"
#include "ProjectMars/Civic/CivicService.h"
#include "ProjectMars/Civic/Population/PopulationData.h"
#include "ProjectMars/Controllers/BasePlayerController.h"
#include "ProjectMars/Delegates/DelegateController.h"
#include "ProjectMars/UI/Widgets/BaseGameplayWidget.h"
#include "ProjectMars/UI/Widgets/ChooseFactionWidget.h"
#include "ProjectMars/UI/Widgets/DevInfo/DevInfoWidget.h"
#include "Widgets/EconomyWidget.h"
#include "Widgets/Events/EventPopupWidget.h"
#include "ProjectMars/Military/Army.h"
#include "ProjectMars/Economy/Data/EconomyData.h"
#include "ProjectMars/Nation/Nation.h"
#include "ProjectMars/Nation/NationService.h"
#include "Widgets/MainMenuWidget.h"
#include "Widgets/DevInfo/StartButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MainMenu2Widget.h"
#include "Widgets/MainGame/MainGameWidget.h"
#include "Widgets/WidgetComponents/FactionButton.h"

#define OUT

ABaseHUD::ABaseHUD()
{
	bHasStartedSelecting = false;
	SelectionBoxColor = FLinearColor(0.f, 1.f, 0.2f, 0.15f);

	CurrentYear = 0;
	CurrentDate = "";
	DateSuffix = "BCE";
	CurrentSeason = "NO_SEASON_SET";

	UE_LOGFMT(LogTemp, Warning, "HUD has been built");
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

	/*if(bHasStartedSelecting)
	{
		CurrentSelectionPoint = GetMousePosition2D();
		DrawSelectionBox();
	}*/
	
	//DrawFPS();
	//DrawEconomyData(EconomyData);
	DrawDevInfo();

	/*if(EventPopupWidget && EventPopupWidget->DecisionButton)
	{
		if(EventPopupWidget->DecisionButton->IsPressed())
		{
			EventPopupWidget->CloseEventPopup();
		}
	}*/

	//MoveWidgetInViewportWithMouse(EventPopupWidget);
}

void ABaseHUD::DrawFactionInfo()
{
	
}

void ABaseHUD::PopulateDataObjects()
{
	ensure(Nation);
	PopulationData = Nation->GetNationService()->GetCivicService()->GetPopulationService()->GetPopulationData();
}

void ABaseHUD::DrawMainMenu()
{
	
}

void ABaseHUD::AddToViewport(UUserWidget* Widget)
{
	Widget->AddToViewport();
}

void ABaseHUD::RemoveFromParent(UUserWidget* Widget)
{
	Widget->RemoveFromParent();
}

void ABaseHUD::RemoveMainMenuFromParent()
{
	RemoveFromParent(MainMenuWidget);
	//MainMenuWidget->GetParent()->ClearChildren();
	MainMenu2Widget->AddToViewport();
}

void ABaseHUD::RemoveMainMenu2FromParent()
{
	MainMenu2Widget->RemoveFromParent();
	ChooseFactionWidget->AddToViewport();
}

void ABaseHUD::LoadMainWorld()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("DefaultMap"));
	ChooseFactionWidget->RemoveFromParent();
}

ABaseHUD* ABaseHUD::SetNation(const UNation* NationVar)
{
	Nation = NationVar;
	return this;
}

void ABaseHUD::SetDateSuffix(const FString& SuffixVal)
{
	DateSuffix = SuffixVal;
}

void ABaseHUD::InitialiseEconomyData(const UEconomyData* EconomyDataVar)
{
	EconomyData = EconomyDataVar;
}

FVector2D ABaseHUD::GetMonitorResolution()
{
	FVector2D MonitorRes;

	MonitorRes.X = GSystemResolution.ResX;
	MonitorRes.Y = GSystemResolution.ResY;
	
	return MonitorRes;
}

FVector2D ABaseHUD::GetViewportResolution()
{
	FVector2D ViewportSize{};
	
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(OUT ViewportSize);		
	}

	return ViewportSize;
}

FVector2D ABaseHUD::GetCenterOfScreen()
{
	FVector2D ScreenCentre;

	ScreenCentre.X = GetViewportResolution().X / 2;
	ScreenCentre.Y = GetViewportResolution().Y / 2;
	
	return ScreenCentre;
}

FVector2D ABaseHUD::GetMousePosition2D() const
{
	FVector2D MousePos{};
	
	GetOwningPlayerController()->GetMousePosition(OUT MousePos.X, OUT MousePos.Y);

	return MousePos;
}

void ABaseHUD::DrawSelectionBox()
{
	DrawRect(SelectionBoxColor, InitialSelectionPoint.X, InitialSelectionPoint.Y,
		CurrentSelectionPoint.X - InitialSelectionPoint.X, CurrentSelectionPoint.Y - InitialSelectionPoint.Y);

	GetActorsInSelectionRectangle<AArmy>(InitialSelectionPoint, CurrentSelectionPoint, ArmiesUnderSelectionBox, false);

	if (ArmiesUnderSelectionBox.IsValidIndex(0))
	{
		ArmySelected = ArmiesUnderSelectionBox[0];
		if (ArmySelected)
		{
			// Do something with army selected
		}
	}
}

void ABaseHUD::InitialisePointers()
{
	ensure(DelegateController);
	
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	
	MainMenuWidget = CreateWidget<UMainMenuWidget>(OwningPlayerController, MainMenuWidgetClass);
	MainMenu2Widget = CreateWidget<UMainMenu2Widget>(OwningPlayerController, MainMenu2WidgetClass);
	ChooseFactionWidget = CreateWidget<UChooseFactionWidget>(OwningPlayerController, ChooseFactionWidgetClass);
	ChooseFactionWidget->InitialiseFactionButtonsWithSelf();
	
	MainGameWidget = CreateWidget<UMainGameWidget>(OwningPlayerController, MainGameWidgetClass);
	MainGameWidget->SetDelegateController(DelegateController);
	MainGameWidget->InitialiseEvents();
	
	EconomyWidget = CreateWidget<UEconomyWidget>(OwningPlayerController, EconomyWidgetClass);
	EventPopupWidget = CreateWidget<UEventPopupWidget>(OwningPlayerController, EventPopupWidgetClass);
	DevInfoWidget = CreateWidget<UDevInfoWidget>(OwningPlayerController, DevInfoWidgetClass);
	StartButtonWidget = CreateWidget<UStartButtonWidget>(OwningPlayerController, StartButtonWidgetClass);

	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "MainMenu")
	{
		MainMenuWidget->StartButton->OnReleased.AddDynamic(this, &ABaseHUD::RemoveMainMenuFromParent);
		MainMenu2Widget->StartNewGameButton_1->OnReleased.AddDynamic(this, &ABaseHUD::RemoveMainMenu2FromParent);
		ChooseFactionWidget->FactionButton_Rome->OnReleased.AddDynamic(this, &ABaseHUD::LoadMainWorld);
		MainMenuWidget->AddToViewport();
		
		//ChooseFactionWidget->AddToViewport();
	}
	else if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "DefaultMap")
	{
		/*DevInfoWidget->TurnNumberText->SetText(FText::AsNumber(1));
		DevInfoWidget->CurrentTurnOwnerText->SetText(FText::FromString("ROM"));
		DevInfoWidget->AddToViewport();*/

		MainGameWidget->AddToViewport();
		//EventPopupWidget->AddToViewport();
	
		StartButtonWidget->StartText->SetText(FText::FromString("START"));
		StartButtonWidget->StartButton->OnReleased.AddDynamic(this, &ABaseHUD::BroadcastStartButton);
		StartButtonWidget->AddToViewport();

	}
}

void ABaseHUD::DrawEconomyData(const UEconomyData* EconomyDataVar)
{
	if (!BaseGameplayWidget)
	{
		UE_LOGFMT(LogTemp, Error, "BaseGameplayeWidget is null!");
	}
	
	/*FString TreasuryText = "Treasury: " + FString::FromInt(EconomyDataVar->GetTreasury());
	FString ExpensesText = "Expenses: " + FString::FromInt(EconomyDataVar->GetExpenses());
	FString GrossIncomeText = "GrossIncome: " + FString::FromInt(EconomyDataVar->GetSumOfIncome());
	FString NetIncomeText = "NetIncome: " + FString::FromInt(EconomyDataVar->GetNetIncome());
	
	BaseGameplayWidget->Treasury->SetText(FText::FromString(TreasuryText));
	BaseGameplayWidget->Expenses->SetText(FText::FromString(ExpensesText));
	BaseGameplayWidget->GrossIncome->SetText(FText::FromString(GrossIncomeText));
	BaseGameplayWidget->NetIncome->SetText(FText::FromString(NetIncomeText));*/
}

void ABaseHUD::DrawFPS()
{
	if(BaseGameplayWidget)
	{
		BaseGameplayWidget->FPSText->SetText(FText::AsNumber(FPSNum));
	}
}

void ABaseHUD::DrawDevInfo()
{
	// // DevInfoWidget->TurnNumberText->SetText(FText::FromString("Turn Number Text"));
	// DevInfoWidget->SeasonText->SetText(FText::FromString(CurrentSeason));
	// DevInfoWidget->YearText->SetText(FText::FromString(CurrentDate));
	// // DevInfoWidget->CurrentTurnOwnerText->SetText(FText::FromString("Current Turn Owner Text"));
	//
	// // Population
	// const FString TotalPop = FString::Printf(TEXT("Total pop num: %s"), *FString::FormatAsNumber(PopulationData->GetCurrentTotalPopNum()));
	// const FString CitizenPop = FString::Printf(TEXT("Citizen pop num: %s"), *FString::FormatAsNumber(PopulationData->GetCurrentCitizenPopNum()));
	// const FString NonCitizenPop = FString::Printf(TEXT("Non-Citizen pop num: %s"), *FString::FormatAsNumber(PopulationData->GetCurrentNonCitizenPopNum()));
	// const FString AlliedClientPop = FString::Printf(TEXT("Allied/Client pop num: %s"), *FString::FormatAsNumber(PopulationData->GetCurrentAlliedClientPopNum()));
	// const FString SlavePop = FString::Printf(TEXT("Slave pop num: %s"), *FString::FormatAsNumber(PopulationData->GetCurrentSlavePopNum()));
	// const FString ForeignerPop = FString::Printf(TEXT("Foreigner pop num: %s"), *FString::FormatAsNumber(PopulationData->GetCurrentForeignerPopNum()));
	//
	// DevInfoWidget->CurrentTotalPopNum->SetText(FText::FromString(TotalPop));
	// DevInfoWidget->CurrentCitizenPopNum->SetText(FText::FromString(CitizenPop));
	// DevInfoWidget->CurrentNonCitizenPopNum->SetText(FText::FromString(NonCitizenPop));
	// DevInfoWidget->CurrentAlliedClientPopNum->SetText(FText::FromString(AlliedClientPop));
	// DevInfoWidget->CurrentSlavePopNum->SetText(FText::FromString(SlavePop));
	// DevInfoWidget->CurrentForeignerPopNum->SetText(FText::FromString(ForeignerPop));
}

void ABaseHUD::SetYearText(const FString& CurrentDateVar)
{
	CurrentDate = CurrentDateVar;
}

void ABaseHUD::DrawTooltip()
{
	if (!BaseGameplayWidget) return;

	int32 CurrentCount = 0;

	// EconomyWidget->RemoveFromParent();

	if (!BaseGameplayWidget->EconomyText->IsHovered()) { return; }


	/*DrawRect(FLinearColor(0, 0, 0, 0.75), GetMousePosition2D().X + 20, GetMousePosition2D().Y + 20,
		GetMousePosition2D().X + 100, GetMousePosition2D().Y + 50);	*/

	BaseGameplayWidget->SetToolTip(EconomyWidget);
}

void ABaseHUD::DrawEventPopup()
{
	if (!EventPopupWidget) return;

	EventPopupWidget->SetPositionInViewport(StartingEventPopupPosition);
	EventPopupWidget->AddToViewport();
}

void ABaseHUD::MoveWidgetInViewportWithMouse(UUserWidget* EventPopupWidgetToMove)
{
	// TODO: Currently requires a double click if we use the left mouse button rather than single click.
	// TODO: Also clicks on whatever is behind the widget as well as the widget.
	
	if (!EventPopupWidgetToMove) { return; }

	// EventPopupWidgetToMove->bIsFocusable = true;

	if(EventPopupWidgetToMove->IsHovered() && !GetOwningPlayerController()->IsInputKeyDown(EKeys::LeftAlt))
	{
		DistanceBetweenMouseAndLeftSideOfWidget = GetMousePosition2D() - CurrentEventPopupPos;
	}

	if(EventPopupWidgetToMove->IsHovered() && GetOwningPlayerController()->IsInputKeyDown(EKeys::LeftAlt))
	{
		CurrentEventPopupPos = GetMousePosition2D() - DistanceBetweenMouseAndLeftSideOfWidget;
		EventPopupWidgetToMove->SetPositionInViewport(CurrentEventPopupPos);
	}
}

UDevInfoWidget* ABaseHUD::GetDevInfoWidget() const
{
	return DevInfoWidget;
}

void ABaseHUD::BroadcastStartButton()
{
	StartButtonWidget->RemoveFromParent();
	ABasePlayerController* Controller = Cast<ABasePlayerController>(GetOwningPlayerController());
	Controller->StartGame();
}

void ABaseHUD::SubscribeToEvents()
{
	DelegateController->OnNewSeason.AddDynamic(this, &ABaseHUD::UpdateSeasonText);
	DelegateController->OnUpdateDate.AddDynamic(this, &ABaseHUD::SetYearText);
}

ABaseHUD* ABaseHUD::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	DelegateController = DelegateControllerVar;
	ensure(DelegateController);
	SubscribeToEvents();
	return this;
}

void ABaseHUD::UpdateSeasonText(const FString& NewSeasonVar)
{
	CurrentSeason = NewSeasonVar;
}

void ABaseHUD::GetActorsUnderSelectionBox()
{
	
}
