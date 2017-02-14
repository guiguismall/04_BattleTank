// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	if (Throw < 0) Throw = -1;
	if (Throw > 0) Throw = 1;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	if (Throw < 0) Throw = -1;
	if (Throw > 0) Throw = 1;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-1 * Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// get current forward vector
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	// get target forward vector
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	// move forward
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	
	// turn
	auto RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendTurnRight(RightThrow.Z);
	
}

