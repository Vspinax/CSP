// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class CSP_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector EnemyMovement = FVector(1.0f, 0.f, 0.f);

	void Hit();

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category = " Enemy Stat")
		float EnemyHealth;

private:

	UPROPERTY(EditAnywhere)
	float Speed = 150.f;

	UPROPERTY(EditAnywhere)
	float TurnDelayMax = 0.5f;

	UPROPERTY(EditAnywhere)
	float TurnDelayMin = 0.f;

	float CurrentTurnDelay = 0.f;

	UPROPERTY(EditAnywhere)
	UShapeComponent* EnemyRoot = nullptr;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComponent;
	
};
