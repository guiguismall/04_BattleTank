// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// So that tanks have to reload on game start
	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) {
		if (IsBarrelMoving())
			FiringState = EFiringState::Aiming;
		else
			FiringState = EFiringState::Locked;
	}
	else {
		FiringState = EFiringState::Reloading;
	}
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity( this,
									OutLaunchVelocity,
									StartLocation,
									TargetLocation,
									LaunchSpeed,
									false,
									0.f,
									0.f,
									ESuggestProjVelocityTraceOption::DoNotTrace
									))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	CurrentAimDirection = AimDirection;
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	// Elevate Barrel
	Barrel->Elevate(DeltaRotator.Pitch);

	// Rotate Turret
	Turret->Rotate(DeltaRotator.Yaw);
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto CurrentForwardVector = Barrel->GetForwardVector();
	return !CurrentForwardVector.Equals(CurrentAimDirection);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));

		// spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

