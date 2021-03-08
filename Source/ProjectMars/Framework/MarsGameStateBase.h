// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MarsGameStateBase.generated.h"

class APlayerCameraPawn;

enum class EMonthOfYear;

struct FCampaignDateTime;

UCLASS()
class PROJECTMARS_API AMarsGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMarsGameStateBase();

	virtual void BeginPlay() override;

	// Function that initialises the pointers via the player class
	void InitialiseReferences(APlayerCameraPawn* InitPlayer);

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	class ABasePlayerController* PlayerController{ nullptr };

	UPROPERTY()
	APlayerCameraPawn* Player{ nullptr };

	UPROPERTY()
	class ABaseHUD* BaseHUD{ nullptr };

	
/* --- TIME MANAGEMENT --- */
public:
	// Initialises CurrentMonth depending on the current MonthIndex
	void UpdateMonth();

	// Tick function that manages how many seconds it takes for a month to pass - the seconds are determined by the UpdateCheckFrequency variable
	void UpdateGameTime();

	int32 GetMaxDaysInMonthNum();

	// Ptr to FCampaignDateTime struct
	FCampaignDateTime* CampaignDateTime;

	// The last time an update occured in seconds
	float LastUpdateCheckTime;

	// Amount in seconds we want to update our player's faction info
	float UpdateCheckFrequency;

	inline float GetTickRate() const { return TickRate; }
	inline int32 GetCurrentDay() const { return CurrentDay; }
	
protected:
	
private:
	// Copy of EMonthOfYear obj so that can evaluate an if statement (i.e., if(CurrentMonth == EMonthOfYear::January) { // Do something }).
	EMonthOfYear CurrentMonth;

	// Storing the month number to be used in a switch statement
	int32 MonthIndex{};

	// Stores the maximum number of days in a particular month
	float MaxDaysInMonth{};

	// Stores the current day of the month
	int32 CurrentDay{};
	int32 PreviousDay{};
	float DaysPerTick{};

	void CalculateTickRate();
	void CalculateCurrentDay();

	float LastTickCheck{};
	float CurrentTick{};
	float TickRate{};
	float TicksPerMonth{ TickRate * UpdateCheckFrequency };
	float LastDaysPerTickCheck{};
};
