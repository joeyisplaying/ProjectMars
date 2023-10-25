// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EconomyController.generated.h"

struct FEconomyData;

class UFinanceCalculator;
class UStateDelegateController;

UENUM()
enum class EIncomeType : uint8
{
	Tax,
	Trade,
	Production,
	Loot,
	Slaves,

	Max UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EIncomeType, EIncomeType::Max);

UENUM()
enum class EExpenseType : uint8
{
	Army,
	Navy,
	Tribute,
	Corruption,

	Max UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EExpenseType, EExpenseType::Max);

UCLASS()
class PROJECTMARS_API UEconomyController : public UObject
{
	GENERATED_BODY()

public:
	UEconomyController();

	// Getter
	FEconomyData* GetEconomyData() const;
	const TMap<EIncomeType, int32>* GetIncomeSources() const;
	const TMap<EExpenseType, int32>* GetExpenseSources() const;

	// Setter
	UEconomyController* SetEconomyData(FEconomyData* EconomyDataVar);
	
	UFUNCTION()
	void UpdateTreasury();

	UFUNCTION()
	void SubscribeToDelegateEvents(UStateDelegateController* StateDelegateController);

private:
	UPROPERTY()
	UFinanceCalculator* FinanceCalculator{ nullptr };

	// Structs
	FEconomyData* EconomyData{ nullptr };

	// Maps
	UPROPERTY()
	TMap<EIncomeType, int32> IncomeSources;
	UPROPERTY()
	TMap<EExpenseType, int32> ExpenseSources;

	// Functions
	UFUNCTION()
	void InitialiseMonetarySources();
};
