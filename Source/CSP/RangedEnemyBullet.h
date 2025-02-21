// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangedEnemyBullet.generated.h"

class UShapeComponent;

UCLASS()
class CSP_API ARangedEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedEnemyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = " Bullet Stat")
		float Speed = 230.f;


	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroyed = 5.f;

	float TimeLived = 0.f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);


};
