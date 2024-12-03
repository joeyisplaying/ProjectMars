// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDProcessor.h"

#include "ProjectMars/UI/BaseHUD.h"

void UPlayerHUDProcessor::Main()
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to process player HUD; HUD was null."));
		return;
	}
	
	HUD->SetDelegateController(DelegateController);
	// HUD->PopulateDataObjects();
	HUD->InitialisePointers();

	UE_LOG(LogTemp, Log, TEXT("Successfully processed player HUD"));
}

UPlayerHUDProcessor* UPlayerHUDProcessor::SetBaseHUD(ABaseHUD* BaseHUD)
{
	this->HUD = BaseHUD;
	return this;
}

UPlayerHUDProcessor* UPlayerHUDProcessor::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	this->DelegateController = DelegateControllerVar;
	ensure(DelegateController);
	SubscribeToEvents();
	return this;
}

void UPlayerHUDProcessor::SubscribeToEvents()
{
	// Setup events
}
