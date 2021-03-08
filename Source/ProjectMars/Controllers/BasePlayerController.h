// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMARS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

	bool bGameIsPaused = true;

	void PauseGame();

protected:
	virtual void BeginPlay() override;

private:
	void SelectionPressed();
	void SelectionReleased();

	UPROPERTY()
	class ABaseHUD* HUD{ nullptr };
};
