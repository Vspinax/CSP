// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy"));
	RootComponent = EnemyRoot;
	EnemyRoot->SetGenerateOverlapEvents(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(EnemyRoot);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(EnemyRoot);

	EnemyHealth = 8;

	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	EnemyMovement = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	EnemyMovement.Normalize();
	SetActorRotation(EnemyMovement.Rotation());

	CollisionSphere->SetGenerateOverlapEvents(true);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += (EnemyMovement * Speed * DeltaTime);
	SetActorLocation(NewLocation);

	CurrentTurnDelay -= DeltaTime;

	if (CurrentTurnDelay < 0.f)
	{
		EnemyMovement = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		EnemyMovement.Normalize();
		SetActorRotation(EnemyMovement.Rotation());

		CurrentTurnDelay = FMath::FRandRange(TurnDelayMin, TurnDelayMax);
	}

	if (EnemyHealth <= 0)
	{
		Destroy();
	}
}

void AEnemy::Hit()
{
}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor->IsA(AMainCharacter::StaticClass()))
	//{
	//	//// Alternetivt : Cast<AEnemy>(OtherActor)->Hit(); 
	//	//Cast<AEnemy>(OtherActor)->Destroy();

	//	////Destroy Bullet:
	//	//Destroy();

	//	UE_LOG(LogTemp, Warning, TEXT("Player Hit"))
	//	AMainCharacter* TempHp = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//	TempHp->TakeDamage();
	//	Destroy();

	//}

	if (OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Hit"))
			AMainCharacter* TempHp = Cast<AMainCharacter>(OtherActor);
			TempHp->TakeDamage();
			Destroy();
		}
	}
}

