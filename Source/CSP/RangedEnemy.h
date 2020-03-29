// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "RangedEnemy.generated.h"


UCLASS()
class CSP_API ARangedEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector EnemyRotation = FVector(1.0f, 0.f, 0.f);


private:

	UPROPERTY(EditAnywhere)
		float TurnDelayMax = 0.5f;

	UPROPERTY(EditAnywhere)
		float TurnDelayMin = 0.f;

	float CurrentTurnDelay = 0.f;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RangedEnemyRoot = nullptr;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComponent;

};
