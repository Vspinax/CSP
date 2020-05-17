// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class Enemy;


UCLASS()
class CSP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Spawn")
		class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<class AEnemy> PawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float SpawnTimer;
		
	float SpawnCharge;

	UFUNCTION(BlueprintPure, Category = "Spawn")
		FVector GetSpawnPoint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category ="Spawn")
	void SpawnOurPawn(UClass* ToSpawn, const FVector& Location);

	//UPROPERTY(EditAnywhere, Category = "Pawn Setup")
	//	TSubclassOf<AEnemy> EnemyBlueprint;
};
