// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// get player tank
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ThisPawn = GetPawn();
	if (!PlayerPawn || !ThisPawn) { return; }
	ATank* PlayerTank = Cast<ATank>(PlayerPawn);
	ATank* ThisTank = Cast<ATank>(ThisPawn);

	// move to player
	MoveToActor(PlayerTank, 0);

	// aim at player
	ThisTank->AimAt(PlayerTank->GetActorLocation());

	// fire
	//ThisTank->Fire();
}

