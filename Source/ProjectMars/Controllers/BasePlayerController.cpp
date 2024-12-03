// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "PlayerHUDProcessor.h"
#include "Components/TextBlock.h"
#include "Logging/StructuredLog.h"
#include "ProjectMars/Civic/Settlement.h"
#include "ProjectMars/Delegates/DelegateController.h"
#include "ProjectMars/Delegates/NationDelegateController.h"
#include "ProjectMars/Framework/MarsGameStateBase.h"
#include "ProjectMars/Nation/Nation.h"
#include "ProjectMars/Player/ProjectMarsPlayer.h"
#include "ProjectMars/UI/BaseHUD.h"
#include "ProjectMars/UI/Widgets/DevInfo/DevInfoWidget.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	UE_LOG(LogTemp, Warning, TEXT("ABasePlayerController::CONSTRUCTOR"));

	NationDelegateController = NewObject<UNationDelegateController>();

	// This is experimental, I think this sets a new HUD for the player
	if (false)
	{
		const TSubclassOf<ABaseHUD> ClientHUD;
		ClientSetHUD(ClientHUD);
	}
	
	bMyTurn = false;
	TurnNumber = 1;
	
	UE_LOGFMT(LogTemp, Warning, "Player Controller has been built");
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("Enter", IE_Released, this, &ABasePlayerController::OnEnter);
	
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ABasePlayerController::OnLMBClick);
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ABasePlayerController::OnRMBClick);

	// Player Pawn Movement
	InputComponent->BindAxis("MoveForward", this, &ABasePlayerController::MovePlayerPawnForwardOrBack);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::MovePlayerPawnRightOrLeft);
}

void ABasePlayerController::SetupHUD()
{
	NewObject<UPlayerHUDProcessor>()
		->SetBaseHUD(Cast<ABaseHUD>(GetHUD()))
		->SetDelegateController(DelegateController)
		->Main();
}

ABasePlayerController* ABasePlayerController::InitialisePawn()
{
	PlayerPawn = Cast<AProjectMarsPlayer>(GetPawn());
	ensure(PlayerPawn);
	return this;
}

void ABasePlayerController::SubscribeToDelegates(UDelegateController* DelegateControllerVar)
{
	DelegateControllerVar->OnChangeTurnOwner.AddDynamic(this, &ABasePlayerController::CheckForMyTurn);
	DelegateControllerVar->OnStartNewTurn.AddDynamic(this, &ABasePlayerController::StartNewTurn);
	
}

void ABasePlayerController::StartGame()
{
	UE_LOGFMT(LogTemp, Warning, "GAME STARTED");
	DelegateController->OnStartNewGame.Broadcast();
}

UNation* ABasePlayerController::GetNation() const
{
	return Nation;
}

ABasePlayerController* ABasePlayerController::SetDelegateController(UDelegateController* DelegateControllerVar)
{
	DelegateController = DelegateControllerVar;
	return this;
}

ABasePlayerController* ABasePlayerController::SetNation(UNation* NationVar)
{
	Nation = NationVar;
	Nation->SetFactionTag("ROM");
	return this;
}

void ABasePlayerController::MovePlayerPawnForwardOrBack(float Val)
{
	if (!PlayerPawn)
	{
		UE_LOGFMT(LogTemp, Error, "Player pawn is null");
		return;
	}
	PlayerPawn->MoveForwardOrBack(Val);
}

void ABasePlayerController::MovePlayerPawnRightOrLeft(float Val)
{
	if (!PlayerPawn)
	{
		UE_LOGFMT(LogTemp, Error, "Player pawn is null");
		return;
	}
	PlayerPawn->MoveRightOrLeft(Val);
}

void ABasePlayerController::OnLMBClick()
{
	FHitResult LeftClick;
	if (GetHitResultUnderCursor(ECC_Visibility, true, LeftClick))
	{
		AActor* Actor = LeftClick.GetActor();
		
		if (!Actor) return;
		
		// PlayerPawn->FilterActorClickedOn(Actor);

		if (Actor->IsA(ASettlement::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("SETTLEMENT CLICKED"));
			ASettlement* Settlement = Cast<ASettlement>(Actor);
			Settlement->SettlementClicked();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SOMETHING ELSE CLICKED"));
		}
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AMarsGameStateBase>(GetWorld()->GetGameState());
	GameState->AddToPlayerControllersList(this);
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABasePlayerController::OnRMBClick()
{
	PlayerPawn->IssueMoveArmyOrder();
}

void ABasePlayerController::OnEnter()
{
	// TODO: Add if-statement to check if player is owner of turn
	DelegateController->OnEndTurn.Broadcast();
}

void ABasePlayerController::CheckForMyTurn(const FString& CurrentTurnOwnerTag)
{
	if (!Nation)
	{
		UE_LOGFMT(LogTemp, Error, "Nation is null");
	} 

	const UDevInfoWidget* Widget = HUD->GetDevInfoWidget();
	Widget->CurrentTurnOwnerText->SetText(FText::FromString(CurrentTurnOwnerTag));
	if (CurrentTurnOwnerTag == Nation->GetFactionTag())
	{
		bMyTurn = true;
		return;
	}
	bMyTurn = false;
}

void ABasePlayerController::StartNewTurn(const int32 TurnNumberVar)
{
	TurnNumber = TurnNumberVar;
	const UDevInfoWidget* Widget = HUD->GetDevInfoWidget();
	Widget->TurnNumberText->SetText(FText::AsNumber(TurnNumberVar));
}
