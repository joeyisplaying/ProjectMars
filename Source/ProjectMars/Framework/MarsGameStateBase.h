// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "MarsGameStateBase.generated.h"

class USettlementFactory;
class AProjectMarsPlayer;
class UDelegateController;
class UNation;
class UTurnController;
class USeasonController;
class UYearController;
class ABasePlayerController;

UCLASS()
class PROJECTMARS_API AMarsGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMarsGameStateBase();

	// Functions
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddPlayerToPlayerArray(AProjectMarsPlayer* ProjectMarsPlayer);

	UFUNCTION()
	void AddToPlayerControllersList(ABasePlayerController* PlayerController);

	UFUNCTION()
	void LoadFirstTurn();

	// Getters
	UFUNCTION()
	UDelegateController* GetDelegateController() const;

	// Setters
	UFUNCTION()
	void SetDelegateController(UDelegateController* ptr);

private:
	// Functions
	UFUNCTION()
	void InitialiseFactionTags();

	UFUNCTION()
	void BuildNations();

	UFUNCTION()
	void SetupPlayerControllers();
	
	// Properties
	UPROPERTY(EditAnywhere)
	TMap<FString, UNation*> Nations;

	UPROPERTY()
	TArray<ABasePlayerController*> AllPlayerControllers;
	
	UPROPERTY(EditAnywhere)
	TArray<AProjectMarsPlayer*> AllPlayers;
	
	UPROPERTY(EditAnywhere)
	UDelegateController* DelegateController{ nullptr };

	UPROPERTY(EditAnywhere)
	UTurnController* TurnController{ nullptr };

	UPROPERTY(EditAnywhere)
	TArray<FString> FactionTags;

	UPROPERTY(EditAnywhere)
	USeasonController* SeasonController{ nullptr };

	UPROPERTY(EditAnywhere)
	UYearController* YearController{ nullptr };

	UPROPERTY(EditAnywhere)
	USettlementFactory* SettlementFactory{ nullptr };

protected:
	virtual void Tick(float DeltaSeconds) override;
};