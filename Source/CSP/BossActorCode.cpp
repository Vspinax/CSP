// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActorCode.h"
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
ABossActorCode::ABossActorCode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BossRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Boss"));
	RootComponent = BossRoot;
	BossRoot->SetGenerateOverlapEvents(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(BossRoot);

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->InitSphereRadius(2000.f);

	BossHealth = 250;
	ReloadTime = 0.5;
	ShootAvailable = 0;

	InRange = false;

}

// Called when the game starts or when spawned
void ABossActorCode::BeginPlay()
{
	Super::BeginPlay();

	EnemyRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	EnemyRotation.Normalize();
	SetActorRotation(EnemyRotation.Rotation());

	BossRoot->OnComponentBeginOverlap.AddDynamic(this, &ABossActorCode::BoxOnOverlapBegin);

	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &ABossActorCode::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &ABossActorCode::AgroSphereOnOverlapEnd);
	
}

// Called every frame
void ABossActorCode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTurnDelay -= DeltaTime;
	ShootAvailable += DeltaTime;

	if (InRange)
	{
		if (ShootAvailable > ReloadTime)
		{
			Shoot();
			ShootAvailable = 0;
			//UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Shot"))
		}
	}

	if (CurrentTurnDelay < 0.f)
	{
		EnemyRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		EnemyRotation.Normalize();
		SetActorRotation(EnemyRotation.Rotation());

		CurrentTurnDelay = FMath::FRandRange(TurnDelayMin, TurnDelayMax);
	}

	if (BossHealth <= 0)
	{
		Destroy();
	}

}

void ABossActorCode::Shoot()
{

	FVector ShootingSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 30.f);
	FRotator ShootingSpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<ARangedEnemyBullet>(BulletBlueprint, ShootingSpawnLocation, ShootingSpawnRotation);

}

void ABossActorCode::BoxOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABullet::StaticClass()))
	{
		ABullet* Bullet = Cast<ABullet>(OtherActor);
		BossHealth -= 2;
		Bullet->Destroy();

		//if (BossHealth <= 0)
		//{
		//	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		//	Main->BossKill++;
		//}
	}

	if (OtherActor->IsA(ASpecialAttackBullet::StaticClass()))
	{
		ASpecialAttackBullet* SpecialAttackBullet = Cast<ASpecialAttackBullet>(OtherActor);
		BossHealth -= 20;

		//if (BossHealth <= 0)
		//{
		//	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		//	Main->BossKill++;
		//}

	}

}

void ABossActorCode::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{

		InRange = true;
		UE_LOG(LogTemp, Warning, TEXT("Player In Range"))
	}

}

void ABossActorCode::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{

		InRange = false;
		UE_LOG(LogTemp, Warning, TEXT("Player Outside Range"))
	}
}

