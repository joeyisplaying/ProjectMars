// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerControllerProcessor.generated.h"

class ABasePlayerController;
class UDelegateController;

/**
 * Called by the Game State
 */
UCLASS()
class PROJECTMARS_API UPlayerControllerProcessor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Main();

	UFUNCTION()
	virtual UPlayerControllerProcessor* SetDelegateController(UDelegateController* DelegateControllerVar);
	
	UFUNCTION()
	UPlayerControllerProcessor* SetPlayerControllerList(TArray<ABasePlayerController*> const &PlayerControllerListVar);

private:
	UPROPERTY()
	TArray<ABasePlayerController*> PlayerControllerList;

	UPROPERTY(EditAnywhere)
	UDelegateController* DelegateController{ nullptr };
};
