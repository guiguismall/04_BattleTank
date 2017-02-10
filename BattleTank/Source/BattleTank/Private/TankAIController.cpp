// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"


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
	if (!ensure(PlayerPawn && ThisPawn)) { return; }

	auto AimingComponent = ThisPawn->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	// move to player
	MoveToActor(PlayerPawn, 0);

	// aim at player
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	// fire
	//ThisPawn->Fire();
}

