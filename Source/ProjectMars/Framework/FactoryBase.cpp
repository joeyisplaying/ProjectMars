// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryBase.h"

#include "SpawnableActor.h"

class UFactoryBase* UFactoryBase::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	DelegateController = DelegateControllerVar;
	return this;
}

UDelegateController* UFactoryBase::GetDelegateController()
{
	return DelegateController;
}

UFactoryBase* UFactoryBase::SetWorld(UWorld* WorldVar)
{
	World = WorldVar;
	return this;
}

UWorld* UFactoryBase::GetWorld()
{
	return World;
}
