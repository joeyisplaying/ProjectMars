// Fill out your copyright notice in the Description page of Project Settings.


#include "Nation.h"

#include "Logging/StructuredLog.h"
#include "..\Delegates\NationDelegateController.h"
#include "ProjectMars/Civic/Population/PopulationController.h"
#include "ProjectMars/Economy/EconomyController.h"

UNation::UNation()
	:
PopulationController(NewObject<UPopulationController>())
{
	// StateDelegateController
	NationDelegateController = NewObject<UNationDelegateController>();

	// EconomyController
	EconomyController = NewObject<UEconomyController>();
	EconomyController->SubscribeToDelegateEvents(NationDelegateController);
	
	FactionTag = "NONE";
}

UEconomyController* UNation::GetEconomyController() const
{
	return EconomyController;
}

AProjectMarsPlayer* UNation::GetOwningPlayer() const
{
	return OwningPlayer;
}

const UPopulationController* UNation::GetPopulationController() const
{
	return PopulationController;
}

UNation* UNation::SetOwningPlayer(AProjectMarsPlayer* PlayerVar)
{
	OwningPlayer = PlayerVar;
	return this;
}

UNation* UNation::SetEconomyController(UEconomyController* EconomyControllerVar)
{
	this->EconomyController = EconomyControllerVar;
	return this;
}

UNation* UNation::SetFactionTag(const FString& FactionTagVar)
{
	FactionTag = FactionTagVar;
	return this;
}

const FString& UNation::GetFactionTag() const
{
	return FactionTag;
}
