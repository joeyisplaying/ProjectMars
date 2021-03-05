// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMars/Factions/FactionBase.h"
#include "RomeFaction.generated.h"

struct FBaseFactionData;

UCLASS()
class PROJECTMARS_API URomeFaction : public UFactionBase
{
	GENERATED_BODY()
	
public:
	URomeFaction();

	inline FName GetFactionName() const { return FactionName; };

private:	
	FBaseFactionData RomeFactionData;

protected:
	virtual void UpdateCurrentIncome() override;
	virtual FBaseFactionData GetRefToFactionData() override;
	
	
};
