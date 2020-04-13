// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "Engine/World.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnTimer = 1.5f;
	SpawnCharge = 0.f;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnCharge += DeltaTime;

	if (SpawnCharge > SpawnTimer)
	{
		//GetWorld()->SpawnActor<AEnemy>(AEnemyBlueprint);
		SpawnCharge = 0;
	}
}

