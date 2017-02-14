// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"				// so we can implement OnDeath
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) { return; }

	// subscribe our local method to the tank's death event
	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// get player tank
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ThisPawn = GetPawn();
	if (!ensure(PlayerPawn && ThisPawn)) { return; }

	auto AimingComponent = ThisPawn->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	// move to player
	MoveToActor(PlayerPawn, AcceptanceRadius);

	// aim at player
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	// fire
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

