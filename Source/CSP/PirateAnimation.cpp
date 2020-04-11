// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateAnimation.h"
#include "GameFramework/CharacterMovementComponent.h"


void UPirateAnimation::Initialization() {

	if (Pawn == nullptr) {
		Pawn=TryGetPawnOwner();
	}

}


void UPirateAnimation::UpdateAnimationState() {
	
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();
	}

	if (Pawn){
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
}