// Fill out your copyright notice in the Description page of Project Settings.


#include "SettlementFactory.h"

#include "ProjectMars/Civic/Settlement.h"

// TArray<ASettlement*> USettlementFactory::BuildSettlements(UDelegateController* DelegateController)
// {
// 	const FVector Location = FVector(0.0f, -10.0f, 20.0f);
// 	const FRotator Rotation = FRotator(0, 0, 0);
// 	FActorSpawnParameters SpawnParameters;
//
// 	TArray<ASettlement*> USettlements;
// 	ASettlement* Settlement = GetWorld()->SpawnActor<ASettlement>(Location, Rotation, SpawnParameters);
// 	Settlement->SetDelegateController(DelegateController);
// 	USettlements.Add(Settlement);
// 	return USettlements;	
// }

// void USettlementFactory::Create(UWorld* WorldVar)
// {
// 	const FVector Location = FVector(610.000000f,70.000000f,20.000000f);
// 	const FRotator Rotation = FRotator(0, 0, 0);
// 	
// 	WorldVar->SpawnActor<ASettlement>(Location, Rotation);
// }


ASettlement* USettlementFactory::Create(const FVector& Location, const FRotator& Rotation) const
{
	ensure(World);
	ensure(DelegateController);
	
	const FActorSpawnParameters SpawnParameters;
	
	ASettlement* Settlement = World->SpawnActor<ASettlement>(Location, Rotation, SpawnParameters);
	Settlement->SetDelegateController(DelegateController);
	
	return Settlement;
}
