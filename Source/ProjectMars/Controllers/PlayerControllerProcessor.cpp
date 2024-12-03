// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerProcessor.h"

#include "BasePlayerController.h"

void UPlayerControllerProcessor::Main()
{
	ensure(DelegateController);
	for (auto* Controller : PlayerControllerList)
	{
		Controller
			->SetDelegateController(DelegateController)
			->InitialisePawn()
			->SetupHUD();
	}	
}

UPlayerControllerProcessor* UPlayerControllerProcessor::SetDelegateController(
	UDelegateController* DelegateControllerVar)
{
	this->DelegateController = DelegateControllerVar;
	return this;
}

UPlayerControllerProcessor* UPlayerControllerProcessor::SetPlayerControllerList(
	TArray<ABasePlayerController*> const &PlayerControllerListVar)
{
	this->PlayerControllerList = PlayerControllerListVar;
	return this;
}
