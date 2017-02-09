// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
public:
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector&, FVector) const;


	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;			// X coordinate of the crosshair on screen (starting left)
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.333333;	// y coordinate of the crosshair on screen (starting top)
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;			// max distance to check for an object hit (10km)
};
