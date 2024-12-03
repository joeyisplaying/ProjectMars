// Fill out your copyright notice in the Description page of Project Settings.


#include "Settlement.h"

#include "Components/BoxComponent.h"
#include "ProjectMars/Delegates/DelegateController.h"
#include "ProjectMars/UI/Widgets/WidgetComponents/SettlementWidgetComponent.h"

// Sets default values
ASettlement::ASettlement()
{
	// /Game/Civic/Materials/MI_City.MI_City
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	RootComponent = Root;
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("City Mesh");
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObject(TEXT("/Game/Civic/StaticMeshes/SM_Settlement.SM_Settlement"));
	StaticMesh->SetStaticMesh(MeshObject.Object);
	StaticMesh->SetGenerateOverlapEvents(false);
	// const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObject(TEXT("/Game/Civic/Materials/MI_City.MI_City"));
	// StaticMesh->SetMaterial(0, MaterialObject.Object);
	StaticMesh->SetupAttachment(Root);

	SettlementWidgetComponent = CreateDefaultSubobject<USettlementWidgetComponent>("Settlement Widget Component");
	SettlementWidgetComponent->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void ASettlement::BeginPlay()
{
	Super::BeginPlay();
}

void ASettlement::SettlementClicked()
{
	ensure(DelegateController);
	
	DelegateController->OnSettlementClick.Broadcast(this);
}

// Called every frame
void ASettlement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASettlement::InitialiseEvents()
{
	ensure(DelegateController);
}
