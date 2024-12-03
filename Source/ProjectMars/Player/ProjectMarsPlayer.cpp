// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMarsPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectMars/Controllers/BasePlayerController.h"
#include "ProjectMars/Framework/MarsGameStateBase.h"
#include "ProjectMars/UI/BaseHUD.h"
#include "DrawDebugHelpers.h"
#include "Logging/StructuredLog.h"
#include "Math/TransformCalculus3D.h"
#include "ProjectMars/Civic/Settlement.h"
#include "ProjectMars/Military/Army.h"

AProjectMarsPlayer::AProjectMarsPlayer()
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

	UE_LOGFMT(LogTemp, Warning, "Player Pawn has been built");
}

// Called when the game starts or when spawned
void AProjectMarsPlayer::BeginPlay()
{
	Super::BeginPlay();

	// MarsGameStateBase
	MarsGameStateBase = Cast<AMarsGameStateBase>(GetWorld()->GetGameState());
	ensure(MarsGameStateBase);

	MarsGameStateBase->AddPlayerToPlayerArray(this);
	InitialisePointers();
	
	SubscribeToDelegateEvents();

	/*UGameplayStatics::OpenLevel(GetWorld(), "ChooseFaction");
	CurrentLevel = GetWorld()->GetMapName();*/
}

// Called every frame
void AProjectMarsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlayerPawn(DeltaTime);
}

void AProjectMarsPlayer::InitialisePointers()
{
	 // Initialise MarsGameStateBase, PlayerState, PlayerController and HUD here. 


	// PlayerState
	MyPlayerState = GetPlayerState();
	ensure(MyPlayerState);

	// PlayerController
	BasePlayerController = Cast<ABasePlayerController>(GetController());
	ensure(BasePlayerController);
	
	// HUD
	BaseHUD = Cast<ABaseHUD>(BasePlayerController->GetHUD());
	ensure(BaseHUD);
}

void AProjectMarsPlayer::SubscribeToDelegateEvents()
{
	// Subscribe to delegate events
}

void AProjectMarsPlayer::MovePlayerPawn(float DeltaTime)
{
	if(!MovementDirection.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed);
		SetActorLocation(NewLocation);
	}
}

// Checks which type of actor was clicked on by the Player
void AProjectMarsPlayer::FilterActorClickedOn(AActor* ActorVar)
{
	ActorClickedOn = ActorVar;
	ArmyClickedOn = Cast<AArmy>(ActorVar);
	if (ArmyClickedOn && ClickCounter == 0)
	{
		// Do something with army
		UE_LOGFMT(LogTemp, Display, "Army clicked on");
		ClickCounter = 1;
	}
	else
	{
		// TODO: Refactor - the click counter is designed to determine whether an actor has already been click on or not
		// This should clear when the player clicks on open space
		UE_LOGFMT(LogTemp, Display, "Empty space clicked on");
		ClickCounter = 0;
	}
}

void AProjectMarsPlayer::MoveForwardOrBack(float Val)
{
	// The FMath::Clamp helps to prevent higher speeds when pressing two keyboard keys at once
	MovementDirection.X = FMath::Clamp(Val, -1.f, 1.f);
}

void AProjectMarsPlayer::MoveRightOrLeft(float Val)
{
	// The FMath::Clamp helps to prevent higher speeds when pressing two keyboard keys at once
	MovementDirection.Y = FMath::Clamp(Val, -1.f, 1.f);
}

void AProjectMarsPlayer::IssueMoveArmyOrder()
{
	if (!ArmyClickedOn) return;

	// TODO: Potentially need to refactor this so that the controller calls the pawn, not the other way around
	FHitResult RightClickLoc;
	if(BasePlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, RightClickLoc))
	{
		// TODO: Need to change this so that we can only right click on appropriate actors such as terrain, or cities, or other armies etc.
		if(RightClickLoc.GetActor())
		{
			ArmyClickedOn->SetTargetLocation(FVector(RightClickLoc.ImpactPoint.X, RightClickLoc.ImpactPoint.Y, RightClickLoc.GetActor()->GetActorLocation().Z));
			DrawDebugBox(GetWorld(), RightClickLoc.ImpactPoint, FVector(25.f, 25.f, 25.f), FColor::Yellow, false, 4.f, 0, 2.f);
		}
	}
}