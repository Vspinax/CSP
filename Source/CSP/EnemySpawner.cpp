// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"




// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	
	//SpawnTimer = 1.5f;
	//SpawnCharge = 0.f;
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

	//SpawnCharge += DeltaTime;

	//if (SpawnCharge > SpawnTimer)
	//{
	//	//GetWorld()->SpawnActor<AEnemy>(AEnemyBlueprint);
	//	SpawnCharge = 0;
	//}
}

FVector AEnemySpawner::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent();
	FVector Origin = SpawningBox->GetComponentLocation();

	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);


	return Point;
}



void AEnemySpawner::SpawnOurPawn_Implementation(UClass* ToSpawn, const FVector& Location)	//Unreal engines knows its scripted in c++, part of it will be carried out in blueprints
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;

		if (World)
		{
			AEnemy* EnemySpawn = World->SpawnActor<AEnemy>(ToSpawn, Location, FRotator(0.f), SpawnParams);
		}
	}
}

