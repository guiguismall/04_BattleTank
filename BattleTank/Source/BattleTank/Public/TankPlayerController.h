// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector&, FVector) const;


	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;			// X coordinate of the crosshair on screen (starting left)
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.333333;	// y coordinate of the crosshair on screen (starting top)
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;			// max distance to check for an object hit (10km)
};
