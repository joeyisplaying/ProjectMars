﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OutgoingsCalculator.generated.h"

enum class EOutgoingsSourceType : uint8;

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UOutgoingsCalculator : public UObject
{
	GENERATED_BODY()

public:
	int32 CalculateOutgoings(const TMap<EOutgoingsSourceType, int32>& MapOfOutgoingsSourcesVar);
	
private:
	
};