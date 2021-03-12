// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMars/UI/BaseHUD.h"

#include "Engine.h"
#include "Components/TextBlock.h"
#include "ProjectMars/Framework/MarsGameStateBase.h"
#include "ProjectMars/Player/ProjectMarsPlayer.h"
#include "ProjectMars/UI/Widgets/BaseGameplayWidget.h"
#include "Widgets/ChooseFactionWidget.h"

#define OUT

ABaseHUD::ABaseHUD()
{
	bHasStartedSelecting = false;
	SelectionBoxColor = FLinearColor(0.f, 1.f, 0.2f, 0.15f);

	DateSuffix = "BCE";
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AProjectMarsPlayer>(GetOwningPlayerController()->GetPawn());

	BaseGameplayWidget = CreateWidget<UBaseGameplayWidget>(GetOwningPlayerController(), BaseGameplayWidgetClass);

	ChooseFactionWidget = CreateWidget<UChooseFactionWidget>(GetOwningPlayerController(), ChooseFactionWidgetClass);
	if (ChooseFactionWidget)
	{
		ChooseFactionWidget->AddToViewport();
		ChooseFactionWidget->OnChooseFaction.AddDynamic(this, &ABaseHUD::DrawMainGameUI);
	}
}

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

	if(bHasStartedSelecting)
	{
		CurrentSelectionPoint = GetMousePosition2D();
		DrawSelectionBox();
	}

	DrawPlayerTreasury();
	DrawDate();
	DrawFPS();
}

FVector2D ABaseHUD::GetMonitorResolution()
{
	FVector2D MonitorRes{};

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
	FVector2D ScreenCentre{};

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
}

void ABaseHUD::InitialiseFactionBase(AFactionBase* InitFactionBase)
{
	FactionBase = InitFactionBase;
}

void ABaseHUD::DrawPlayerTreasury()
{
	if(BaseGameplayWidget && Player)
	{
		//BaseGameplayWidget->EconomyText->SetText(FText::FromString(FString::SanitizeFloat(Player->PlayerEconomy.Treasury)));
		BaseGameplayWidget->EconomyText->SetText(FText::AsNumber(Player->PlayerEconomy.Treasury));
	}
}

void ABaseHUD::DrawDate()
{	
	if(BaseGameplayWidget && Player)
	{
		BaseGameplayWidget->DayText->SetText(FText::AsNumber(Player->MarsGameStateBase->GetCurrentDay()));
		BaseGameplayWidget->MonthText->SetText(FText::FromString(Player->MarsGameStateBase->GetCurrentMonthName()));
		BaseGameplayWidget->YearText->SetText(FText::AsNumber(Player->MarsGameStateBase->GetCurrentYear()));
		BaseGameplayWidget->DateSuffixText->SetText(FText::FromString(DateSuffix));
	}
}

void ABaseHUD::DrawFPS()
{
	if(BaseGameplayWidget)
	{
		BaseGameplayWidget->FPSText->SetText(FText::AsNumber(FPSNum));
	}
}

// TODO: Currently set up so that any button we click will choose Rome - need to make out faction choice relate to the button we press
void ABaseHUD::DrawMainGameUI()
{
	if(ChooseFactionWidget && BaseGameplayWidget && Player)
	{		
		Player->ChooseRome();
		UE_LOG(LogTemp, Warning, TEXT("Choose Rome"));
		
		ChooseFactionWidget->RemoveFromParent();
		BaseGameplayWidget->AddToViewport();
	}
}