// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PirateAnimation.generated.h"

/**
 * 
 */
UCLASS()
class CSP_API UPirateAnimation : public UAnimInstance
{
	GENERATED_BODY()
public:

		void Initialization();

		UFUNCTION (BlueprintCallable)
		void UpdateAnimationState();

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovementSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class APawn* Pawn;
};
