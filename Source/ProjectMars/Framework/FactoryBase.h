// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FactoryBase.generated.h"

class UDelegateController;
class ASpawnableActor;

/**
 * 
 */
UCLASS()
class PROJECTMARS_API UFactoryBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UFactoryBase* SetDelegateController(UDelegateController* DelegateControllerVar);

	UFUNCTION()
	virtual UDelegateController* GetDelegateController();

	UFUNCTION()
	virtual UFactoryBase* SetWorld(UWorld* WorldVar);

	UFUNCTION()
	virtual UWorld* GetWorld();

protected:
	UPROPERTY(EditAnywhere)
	class UDelegateController* DelegateController{ nullptr };

	UPROPERTY(EditAnywhere)
	class UWorld* World{ nullptr };
	
private:

	
};
