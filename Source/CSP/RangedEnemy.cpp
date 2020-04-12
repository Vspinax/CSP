// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "RangedEnemyBullet.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARangedEnemy::ARangedEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RangedEnemyRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy"));
	RootComponent = RangedEnemyRoot;
	RangedEnemyRoot->SetGenerateOverlapEvents(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RangedEnemyRoot);

	RangedEnemyHealth = 6;
	ReloadTime = 1.5;
	ShootAvailable = 0;
}

// Called when the game starts or when spawned
void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	EnemyRotation.Normalize();
	SetActorRotation(EnemyRotation.Rotation());
	
}

// Called every frame
void ARangedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentTurnDelay -= DeltaTime;
	ShootAvailable += DeltaTime;

	if (ShootAvailable > 1.5f)
	{
		Shoot();
		ShootAvailable = 0;
	}


	if (CurrentTurnDelay < 0.f)
	{
		EnemyRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		EnemyRotation.Normalize();
		SetActorRotation(EnemyRotation.Rotation());

		CurrentTurnDelay = FMath::FRandRange(TurnDelayMin, TurnDelayMax);
	}

	if (RangedEnemyHealth <= 0)
	{
		Destroy();
	}

}

void ARangedEnemy::Shoot()
{
	/*GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 150.f,
		GetActorRotation());*/

		// the number is the offsett of the bullet, the distance from the character where the  bullet will spawn

	FVector ShootingSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 50.f);
	FRotator ShootingSpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<ARangedEnemyBullet>(BulletBlueprint, ShootingSpawnLocation, ShootingSpawnRotation);

}

