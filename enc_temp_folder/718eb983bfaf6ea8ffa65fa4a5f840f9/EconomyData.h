// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EconomyData.generated.h"

/**
 * 
 */
USTRUCT()
struct PROJECTMARS_API FEconomyData
{
	GENERATED_BODY()

public:
	FEconomyData();
	FEconomyData(float MoneyVal);
	
	float GetMoney() const { return Money; }
	void SetMoney(int32 aMoney) { Money = aMoney; }
	float GetTaxRate() const { return TaxRate; }
	void SetTaxRate(float aTaxRate) { TaxRate = aTaxRate; }
	
	float Money{};
	float TaxRate{};	
};
