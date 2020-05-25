// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();

	}


}

void UMyAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();

	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size(); 



	}
}


