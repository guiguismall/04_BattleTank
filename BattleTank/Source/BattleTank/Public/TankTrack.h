// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/*
	Used to apply driving force to the tank
*/

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Max force per track in newtons
	//UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 20000000.0;	// assume 40 tons tank, going for 10m/s^2 accel
};
