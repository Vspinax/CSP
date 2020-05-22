// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "RangedEnemyBullet.h"
#include "MainCharacter.h"
#include "Bullet.h"
#include "SpecialAttackBullet.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
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

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->InitSphereRadius(1000.f);

	RangedEnemyHealth = 6;
	ReloadTime = 1.5;
	ShootAvailable = 0;

	InRange = false;
}

// Called when the game starts or when spawned
void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	EnemyRotation.Normalize();
	SetActorRotation(EnemyRotation.Rotation());

	RangedEnemyRoot->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemy::BoxOnOverlapBegin);

	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemy::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &ARangedEnemy::AgroSphereOnOverlapEnd);
	
}

// Called every frame
void ARangedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentTurnDelay -= DeltaTime;
	ShootAvailable += DeltaTime;

	if (InRange)
	{
		if (ShootAvailable > 1.5f)
		{
			Shoot();
			ShootAvailable = 0;
			UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Shot"))
		}
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

	FVector ShootingSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 30.f);
	FRotator ShootingSpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<ARangedEnemyBullet>(BulletBlueprint, ShootingSpawnLocation, ShootingSpawnRotation);

}

void ARangedEnemy::BoxOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABullet::StaticClass()))
	{
		ABullet* Bullet = Cast<ABullet>(OtherActor);
		RangedEnemyHealth -= 2;
		Bullet->Destroy();
	}

	if (OtherActor->IsA(ASpecialAttackBullet::StaticClass()))
	{
		ASpecialAttackBullet* SpecialAttackBullet = Cast<ASpecialAttackBullet>(OtherActor);
		RangedEnemyHealth -= 20;

	}

}

void ARangedEnemy::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		//AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		//if (MainCharacter)
		//{
		//	InRange = true;
		//}

		InRange = true;
		UE_LOG(LogTemp, Warning, TEXT("Player In Range"))
	}

}

void ARangedEnemy::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
	/*	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			InRange = false;
		}*/

		InRange = false;
		UE_LOG(LogTemp, Warning, TEXT("Player Outside Range"))
	}
}

