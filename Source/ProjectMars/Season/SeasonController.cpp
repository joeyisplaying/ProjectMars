// Fill out your copyright notice in the Description page of Project Settings.


#include "SeasonController.h"

#include "Logging/StructuredLog.h"
#include "ProjectMars/Delegates/DelegateController.h"
#include "ProjectMars/Utils/ReadWriteJsonFile.h"

USeasonController::USeasonController()
{
	SeasonIndex = 0;
	PopulateListOfSeasons();
	CurrentSeason = StartingSeason;
}

void USeasonController::BroadcastNewSeasonEvent(const int32 TurnNumberVar)
{
	CurrentSeason = ListOfSeasons[SeasonIndex];
	DelegateController->OnNewSeason.Broadcast(CurrentSeason);
	if (SeasonIndex == 0)
	{
		BroadcastNewYear();
	}
	SeasonIndex++;
	if (SeasonIndex > MaxSeasonIndex)
	{
		// Reset SeasonIndex
		SeasonIndex = 0;
	}
	
}

void USeasonController::PopulateListOfSeasons()
{
	ListOfSeasons = {"spring", "summer", "autumn", "winter"};
	
	StartingSeason = ListOfSeasons[0];
	MaxNumberOfSeasons = ListOfSeasons.Num();
	MaxSeasonIndex = MaxNumberOfSeasons - 1;
}

void USeasonController::SubscribeToDelegateEvents(UDelegateController* DelegateControllerVar)
{
	DelegateController->OnFirstTurn.AddDynamic(this, &USeasonController::SetStartTurnSeason);
	DelegateController->OnStartNewTurn.AddDynamic(this, &USeasonController::BroadcastNewSeasonEvent);
}

void USeasonController::BroadcastNewYear()
{
	DelegateController->OnNewYear.Broadcast();
}

const TArray<FString>& USeasonController::GetListOfSeasons() const
{
	return ListOfSeasons;
}

USeasonController* USeasonController::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	DelegateController = DelegateControllerVar;
	return this;
}

void USeasonController::SetStartTurnSeason()
{
	BroadcastNewSeasonEvent(0);
}
