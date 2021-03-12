// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMars/Factions/FactionBase.h"
#include "RomeFaction.generated.h"

UCLASS()
class PROJECTMARS_API ARomeFaction : public AFactionBase
{
	GENERATED_BODY()
	
public:
	ARomeFaction();

	inline FName GetFactionName() const { return FactionName; };

private:	
	FBaseFactionData RomeFactionData;
	FFactionEconomics RomeFactionEconomy;
	FPopulation RomePopulation;
	FCulture RomanCultureData;

protected:
	virtual FBaseFactionData& GetRefToFactionData() override;
	virtual FFactionEconomics& GetRefToEconomicsData() override;
	virtual FPopulation& GetRefToPopulationData() override;
	// virtual FCultureGroup& GetRefToCultureGroup() override;
	virtual FCulture& GetRefToCultureData() override;
};