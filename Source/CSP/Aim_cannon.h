// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Aim_cannon.generated.h"

UCLASS()
class CSP_API AAim_cannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAim_cannon();

	float TurnDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float TurnDelayMax = 0.5f;

	UPROPERTY(EditAnywhere)
		float TurnDelayMin = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector TurretMovement = FVector(1.0f, 0.f, 0.f);

};
