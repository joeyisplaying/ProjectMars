// Fill out your copyright notice in the Description page of Project Settings.


#include "MarsGameStateBase.h"

#include "SettlementFactory.h"
#include "Logging/StructuredLog.h"
#include "ProjectMars/Civic/Settlement.h"
#include "ProjectMars/Controllers/BasePlayerController.h"
#include "ProjectMars/Controllers/PlayerControllerProcessor.h"
#include "ProjectMars/Player/ProjectMarsPlayer.h"
#include "ProjectMars/Delegates/DelegateController.h"
#include "ProjectMars/Nation/Nation.h"
#include "ProjectMars/Nation/NationBuilder.h"
#include "ProjectMars/Season/SeasonController.h"
#include "ProjectMars/Turns/TurnController.h"
#include "ProjectMars/Turns/YearController.h"
#include "ProjectMars/UI/BaseHUD.h"
#include "ProjectMars/Utils/ReadWriteJsonFile.h"

AMarsGameStateBase::AMarsGameStateBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	DelegateController = NewObject<UDelegateController>();

	// Turn Controller
	TurnController = NewObject<UTurnController>();
	TurnController->SetMarsGameStateBase(this);
	TurnController->SetDelegateController(DelegateController);
	TurnController->SubscribeToDelegates(DelegateController);

	// Season Controller
	SeasonController = NewObject<USeasonController>();
	SeasonController->SetDelegateController(DelegateController);
	SeasonController->SubscribeToDelegateEvents(DelegateController);

	// Year Controller
	YearController = NewObject<UYearController>();
	YearController->SetDelegateController(DelegateController);
	YearController->SubToEvents(DelegateController);

	// Settlements
	SettlementFactory = NewObject<USettlementFactory>();
	SettlementFactory->SetWorld(GetWorld());
	SettlementFactory->SetDelegateController(DelegateController);
	
	InitialiseFactionTags();
	// BuildNations();

	UE_LOGFMT(LogTemp, Warning, "Game state has been built");
}

void AMarsGameStateBase::AddPlayerToPlayerArray(AProjectMarsPlayer* ProjectMarsPlayer)
{
	ensure(ProjectMarsPlayer);
	AllPlayers.Add(ProjectMarsPlayer);
	
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(ProjectMarsPlayer->GetController());
	ensure(PlayerController);
	AllPlayerControllers.Add(PlayerController);
	if (AllPlayerControllers.Num() == GetWorld()->GetNumPlayerControllers())
	{
		UE_LOG(LogTemp, Log, TEXT("Starting player setup"));
		
		NewObject<UPlayerControllerProcessor>()
			->SetDelegateController(DelegateController)
			->SetPlayerControllerList(AllPlayerControllers)
			->Main();
		
		UE_LOG(LogTemp, Log, TEXT("Player setup complete"));
		DelegateController->OnPlayerSetupComplete.Broadcast();
	}
}

void AMarsGameStateBase::AddToPlayerControllersList(ABasePlayerController* PlayerController)
{
	// if (!PlayerController)
	// {
	// 	UE_LOG(LogTemp, Fatal, TEXT("Failed to add player controllers to list; PlayerController was null."));
	// 	return;
	// }
	// PlayerController->Tick();
	// AllPlayerControllers.Add(PlayerController);
	// if (AllPlayerControllers.Num() == GetWorld()->GetNumPlayerControllers())
	// {
	// 	// All player controllers added to list - broadcast delegate
	// }
}

void AMarsGameStateBase::LoadFirstTurn()
{
	TurnController->BroadcastFirstTurn();
}

// BeginPlay in the game state is called before BeginPlay in the player class. References will therefore not be initialised in BeginPlay here.
void AMarsGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	// const FVector Location = FVector(610.000000f,70.000000f,20.000000f);
	// const FRotator Rotation = FRotator(0, 0, 0);
	//
	// GetWorld()->SpawnActor<ASettlement>(Location, Rotation);

	const FVector Location = FVector(610.000000f,70.000000f,20.000000f);
	const FRotator Rotation = FRotator(0, 0, 0);
	
	SettlementFactory->Create(Location, Rotation);
}

void AMarsGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UDelegateController* AMarsGameStateBase::GetDelegateController() const
{
	return DelegateController;
}

void AMarsGameStateBase::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	DelegateController = DelegateControllerVar;
}

// Creates array of all faction tags - the order of this array is the order of the turn owners turn
void AMarsGameStateBase::InitialiseFactionTags()
{
	// TODO: Have array populated by JSON file of all faction tags
	bool bSuccess;
	FString Output;
	const FString GameContentDirectory = FPaths::GameSourceDir();
	const FString JsonPath = GameContentDirectory + "ProjectMars/TempJson/Nations/Nations.json";
	const TSharedPtr<FJsonObject> Json = UReadWriteJsonFile::ReadJson(JsonPath, bSuccess, Output);

	if (!bSuccess)
	{
		UE_LOGFMT(LogTemp, Fatal, "Initialising faction tags failed with the following output: {0}", Output);
	}
	
	for (const auto& Elem : Json->Values)
	{
		FactionTags.Add(Elem.Key);
	}
	TurnController->SetFactionTags(FactionTags);
}

// Creates all the nations in the game
void AMarsGameStateBase::BuildNations()
{
	UNationBuilder* NationBuilder = NewObject<UNationBuilder>();
	Nations = NationBuilder->BuildNations(FactionTags);
	for (const auto& Nation : Nations)
	{
		Nation.Value->SubscribeToEvents(DelegateController);
	}
}

void AMarsGameStateBase::SetupPlayerControllers()
{
	for (auto* PlayerController : AllPlayerControllers)
	{
		PlayerController->SetDelegateController(DelegateController);
		PlayerController->SubscribeToDelegates(DelegateController);
		PlayerController->SetNation(*Nations.Find("ROM"));
	}
}
