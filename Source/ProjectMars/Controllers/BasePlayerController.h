// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class AProjectMarsPlayer;
class ABaseHUD;
class UNation;
class UDelegateController;
class UNationDelegateController;
class AMarsGameStateBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRMBPressed);

UCLASS()
class PROJECTMARS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	// Functions
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void SetupHUD();

	UFUNCTION()
	ABasePlayerController* InitialisePawn();

	UFUNCTION()
	void SubscribeToDelegates(UDelegateController* DelegateControllerVar);

	UFUNCTION()
	void StartGame();

	// Getters
	UNation* GetNation() const;
	
	// Setters
	UFUNCTION()
	ABasePlayerController* SetDelegateController(UDelegateController* DelegateControllerVar);

	UFUNCTION()
	ABasePlayerController* SetNation(UNation* NationVar);

	// Properties
	FOnRMBPressed OnRMBPressed;
	
	const bool bIsPlayerController { true };
	
private:
	// Functions
	UFUNCTION()
	void MovePlayerPawnForwardOrBack(float Val);

	UFUNCTION()
	void MovePlayerPawnRightOrLeft(float Val);
	
	UFUNCTION()
	void OnLMBClick();

	UFUNCTION()
	void OnRMBClick();

	UFUNCTION()
	void OnEnter();



	UFUNCTION()
	void CheckForMyTurn(const FString& CurrentTurnOwnerTag);

	UFUNCTION()
	void StartNewTurn(const int32 TurnNumberVar);
	
	// Properties
	UPROPERTY(EditAnywhere)
	AMarsGameStateBase* GameState{ nullptr };
	
	UPROPERTY(EditAnywhere)
	AProjectMarsPlayer* PlayerPawn{ nullptr };
	
	UPROPERTY(EditAnywhere)
	ABaseHUD* HUD{ nullptr };

	UPROPERTY(EditAnywhere)
	bool bMyTurn;

	UPROPERTY(EditAnywhere)
	UNation* Nation{ nullptr };

	UPROPERTY(EditAnywhere)
	UDelegateController* DelegateController{ nullptr };

	UPROPERTY(EditAnywhere)
	UNationDelegateController* NationDelegateController{ nullptr };

	UPROPERTY()
	int32 TurnNumber;
protected:
	virtual void BeginPlay() override;
};
