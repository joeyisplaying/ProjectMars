// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactoryBase.h"
#include "UObject/Object.h"
#include "SettlementFactory.generated.h"

class ASpawnableActor;
class ASettlement;
class UDelegateController;
class UWorld;

/**
 * 
 */
UCLASS()
class PROJECTMARS_API USettlementFactory : public UFactoryBase
{
	GENERATED_BODY()

private:

public:
	UFUNCTION()
	ASettlement* Create(const FVector& Location, const FRotator& Rotation) const;
};
