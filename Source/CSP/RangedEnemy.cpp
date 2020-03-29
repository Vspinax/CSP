// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
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

	if (CurrentTurnDelay < 0.f)
	{
		EnemyRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		EnemyRotation.Normalize();
		SetActorRotation(EnemyRotation.Rotation());

		CurrentTurnDelay = FMath::FRandRange(TurnDelayMin, TurnDelayMax);
	}

}

