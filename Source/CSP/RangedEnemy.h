// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "RangedEnemy.generated.h"

class ARangedEnemyBullet;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class USphereComponent* AgroSphere;

	FVector EnemyRotation = FVector(1.0f, 0.f, 0.f);

	UPROPERTY(EditAnywhere)
		float RangedEnemyHealth;

	UFUNCTION()
		void Shoot();

	UPROPERTY(EditAnywhere, Category = "Pawn Setup")
		TSubclassOf<ARangedEnemyBullet> BulletBlueprint;

	UPROPERTY(EditAnywhere)
		float ReloadTime;

	UPROPERTY(EditAnywhere)
		float ShootAvailable;

	UFUNCTION()
		virtual void BoxOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual	void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);



	bool InRange;

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
