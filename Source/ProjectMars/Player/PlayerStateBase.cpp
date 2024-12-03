// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"

APlayerStateBase::APlayerStateBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("APlayerStateBase::CONSTRUCTOR"));
}

void APlayerStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("APlayerStateBase::BeginPlay"));
}
