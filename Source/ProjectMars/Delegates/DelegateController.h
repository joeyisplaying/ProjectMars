// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DelegateController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSettlementClick, const ASettlement*, Settlement);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonthlyUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerInitialisation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIFactionInitialisation);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewSeason, const FString&, CurrentSeason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartNewGame);

// Turn-based Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirstTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeTurnOwner, const FString&, CurrentTurnOwner);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartNewTurn, const int32, TurnNumber);

// Year Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewYear);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetStartYearSuffix, const FString&, StartSuffixVar);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateYearSuffix, const FString&, UpdateSuffixVar);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateDate, const FString&, DateVar);

// Initialising Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerSetupComplete);

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UDelegateController : public UObject
{
	GENERATED_BODY()
	
public:
	FOnMonthlyUpdate OnMonthlyUpdate;
	FOnPlayerInitialisation OnPlayerInitialisation;
	FOnAIFactionInitialisation OnAIFactionInitialisation;
	FOnEndTurn OnEndTurn;
	FOnStartNewTurn OnStartNewTurn;
	FOnChangeTurnOwner OnChangeTurnOwner;
	FOnFirstTurn OnFirstTurn;
	FOnNewYear OnNewYear;
	FOnNewSeason OnNewSeason;
	FOnStartNewGame OnStartNewGame;
	FOnUpdateDate OnUpdateDate;
	FOnSetStartYearSuffix OnSetStartYearSuffix;
	FOnUpdateYearSuffix OnUpdateYearSuffix;
	FOnSettlementClick OnSettlementClick;
	FOnPlayerSetupComplete OnPlayerSetupComplete;

private:
	
};
