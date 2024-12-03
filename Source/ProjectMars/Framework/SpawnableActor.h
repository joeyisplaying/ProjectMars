// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.generated.h"

class UDelegateController;

UCLASS()
class PROJECTMARS_API ASpawnableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnableActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual ASpawnableActor* SetDelegateController(UDelegateController* DelegateControllerVar);

	UFUNCTION()
	virtual UDelegateController* GetDelegateController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDelegateController* DelegateController{ nullptr };

private:

};
