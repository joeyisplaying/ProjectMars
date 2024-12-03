// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerHUDProcessor.generated.h"

class UDelegateController;
class ABaseHUD;

/**
 * Called by Player Controller.
 * This class sets up everything the player's HUD needs for the game
 */
UCLASS()
class PROJECTMARS_API UPlayerHUDProcessor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Main();

	UFUNCTION()
	UPlayerHUDProcessor* SetBaseHUD(ABaseHUD* BaseHUD);

	UFUNCTION()
	UPlayerHUDProcessor* SetDelegateController(UDelegateController* DelegateControllerVar);

private:
	UPROPERTY()
	ABaseHUD* HUD;

	UPROPERTY()
	UDelegateController* DelegateController{ nullptr };

	UFUNCTION()
	void SubscribeToEvents();
};
