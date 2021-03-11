// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMars/Player/PlayerCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectMars/Controllers/BasePlayerController.h"
#include "ProjectMars/Factions/FactionBase.h"
#include "ProjectMars/Factions/Hellenic/EtruriaFaction.h"
#include "ProjectMars/Factions/Hellenic/RomeFaction.h"
#include "ProjectMars/Factions/Punic/CarthageFaction.h"
#include "ProjectMars/Framework/MarsGameStateBase.h"
#include "ProjectMars/UI/BaseHUD.h"
#include "ProjectMars/Framework/TimeInGame.h"


// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Scene Component/Root Component
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = RootComp;

	// Spring Arm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComp);
	SpringArmComp->bEnableCameraLag = true;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp);

	MovementSpeed = 500.f;

	bHasChosenFaction = false;
	bHasSetTreasury = false;

	MonthIndex = 1;

	// TIME
	FCampaignDateTime Obj;
	CampaignDateTimePtr = &Obj;
}

// Called when the game starts or when spawned
void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	InitialiseGameStateRefs();

	/*UGameplayStatics::OpenLevel(GetWorld(), "ChooseFaction");
	CurrentLevel = GetWorld()->GetMapName();*/
	
	BasePlayerController = Cast<ABasePlayerController>(GetController());
	if(BasePlayerController)
	{
		BaseHUD = Cast<ABaseHUD>(BasePlayerController->GetHUD());
	}
	if(!BasePlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("BasePlayerController is nullptr - APlayerCameraPawn::BeginPlay"));
	}
}

// Called every frame
void APlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PawnMovement(DeltaTime);
}

void APlayerCameraPawn::InitialiseGameStateRefs()
{
	MarsGameStateBase = Cast<AMarsGameStateBase>(GetWorld()->GetGameState());

	if(MarsGameStateBase)
	{
		MarsGameStateBase->InitialiseReferences(this);
	}
	if(!MarsGameStateBase)
	{
		UE_LOG(LogTemp, Error, TEXT("MarsGameStateBase is NULL!"))
	}
}

void APlayerCameraPawn::PawnMovement(float DeltaTime)
{
	if(!MovementDirection.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed);
		SetActorLocation(NewLocation);
	}
}

void APlayerCameraPawn::SetTreasury()
{
	if(FactionEconomics)
	{
		PlayerEconomy.Treasury = FactionEconomics->Treasury;

		UE_LOG(LogTemp, Warning, TEXT("SetTreasury CALLED!"))
		
		bHasSetTreasury = true;
	}
	if(!FactionEconomics)
	{
		UE_LOG(LogTemp, Error, TEXT("FactionEconomics is NULL!"))
	}
}

// Is called by the GameState class
void APlayerCameraPawn::UpdatePlayerFactionInfo()
{
	UpdatePlayerIncome();
	UpdatePlayerPopulationData();
}

void APlayerCameraPawn::MoveForward(float Val)
{
	// The FMath::Clamp helps to prevent higher speeds when pressing two keyboard keys at once
	MovementDirection.X = FMath::Clamp(Val, -1.f, 1.f);
}

void APlayerCameraPawn::MoveRight(float Val)
{
	// The FMath::Clamp helps to prevent higher speeds when pressing two keyboard keys at once
	MovementDirection.Y = FMath::Clamp(Val, -1.f, 1.f);
}

void APlayerCameraPawn::ChooseRome()
{
	if(bHasChosenFaction) { return; }
	InitialisePlayerFaction(EFaction::Rome);
}

void APlayerCameraPawn::ChooseEtruria()
{
	if(bHasChosenFaction) { return; }
	InitialisePlayerFaction(EFaction::Etruria);
}

void APlayerCameraPawn::ChooseCarthage()
{
	if(bHasChosenFaction) { return; }
	InitialisePlayerFaction(EFaction::Carthage);
}

void APlayerCameraPawn::InitialisePlayerFaction(const EFaction& Faction)
{
	if(bHasChosenFaction) { return; }
	
	switch (Faction)
	{
		case EFaction::Rome : PlayerAssignedFaction = NewObject<URomeFaction>();
		break;

		case EFaction::Etruria : PlayerAssignedFaction = NewObject<UEtruriaFaction>();
		break;

		case EFaction::Carthage : PlayerAssignedFaction = NewObject<UCarthageFaction>();
		break;

		default: PlayerAssignedFaction = nullptr;
		break;
	}

	if(PlayerAssignedFaction && MarsGameStateBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("Faction Name: %s"), *PlayerAssignedFaction->GetBaseFactionName().ToString());
		InitialiseHUD(PlayerAssignedFaction);

		// This is a pointer to the address of the faction data object 
		BaseFactionData = &PlayerAssignedFaction->GetRefToFactionData();
		FactionEconomics = &PlayerAssignedFaction->GetRefToEconomicsData();

		bHasChosenFaction = true;
		MarsGameStateBase->LastUpdateCheckTime = GetWorld()->GetTimeSeconds();
	}
	if(!PlayerAssignedFaction)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerAssignedFaction is NULL!"))
	}
}

void APlayerCameraPawn::InitialiseHUD(class UFactionBase* FactionBase)
{
	if(BaseHUD)
	{
		BaseHUD->InitialiseFactionBase(FactionBase);
	}
	if(!BaseHUD)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseHUD is nullptr - APlayerCameraPawn::InitialiseHUD"));
	}
}

void APlayerCameraPawn::UpdatePlayerIncome()
{
	if(PlayerAssignedFaction && !bHasSetTreasury)
	{
		SetTreasury();
	}
	if(PlayerAssignedFaction && bHasSetTreasury)
	{
		AddMoney();
		PlayerAssignedFaction->FactionEconomics.ApplyNetIncomeToTreasury();
		PlayerEconomy.Treasury = FactionEconomics->Treasury;
	}
}

void APlayerCameraPawn::AddMoney()
{
	if(FactionEconomics)
	{
		FactionEconomics->Treasury += 10.f;
		
		UE_LOG(LogTemp, Warning, TEXT("AddMoney CALLED!"))
	}
}

// TODO: May want to refactor this so that it is implemented a little cleaner.
void APlayerCameraPawn::UpdateGameSpeed(float Val)
{
	if(Val == 0) { return; }
	if(!MarsGameStateBase) { return; }
	
	if(Val == 1)
	{
		MarsGameStateBase->UpdateCheckFrequency = 5.f;
		
		UE_LOG(LogTemp, Warning, TEXT("GameSpeed: %f"), Val);
	}
	if(Val == 2)
	{
		MarsGameStateBase->UpdateCheckFrequency = 3.f;

		UE_LOG(LogTemp, Warning, TEXT("GameSpeed: %f"), Val);
	}
	if(Val == 5)
	{
		MarsGameStateBase->UpdateCheckFrequency = 1.f;
		
		UE_LOG(LogTemp, Warning, TEXT("GameSpeed: %f"), Val);
	}	
}

void APlayerCameraPawn::UpdatePlayerPopulationData()
{
	if(PlayerAssignedFaction)
	{
		FPopulation& Pop = PlayerAssignedFaction->GetRefToPopulationData();
		Pop.UpdateMonthlyPopulation();
	}
}

// Called to bind functionality to input
void APlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		// Movement
		PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCameraPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCameraPawn::MoveRight);

		// Economy
		PlayerInputComponent->BindAction("Money", IE_Pressed, this, &APlayerCameraPawn::AddMoney);

		// Game Speed
		PlayerInputComponent->BindAxis("GameSpeed", this, &APlayerCameraPawn::UpdateGameSpeed);
	}
}