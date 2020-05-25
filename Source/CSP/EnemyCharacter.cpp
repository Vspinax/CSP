// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Bullet.h"
#include "SpecialAttackBullet.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->InitSphereRadius(600.f);

	CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	CombatSphere->SetupAttachment(GetRootComponent());
	CombatSphere->InitSphereRadius(75.f);

	EnemyHealth = 8;



}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());
	
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::AgroSphereOnOverlapEnd);

	CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::CombatSphereOnOverlapBegin);
	CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::CombatSphereOnOverlapEnd);

}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyHealth <= 0)
	{
		Destroy();
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			MoveToTarget(MainCharacter);
		}
	}
}
void AEnemyCharacter::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

}
void AEnemyCharacter::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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

	if (OtherActor->IsA(ABullet::StaticClass()))
	{
		ABullet* Bullet = Cast<ABullet>(OtherActor);
		EnemyHealth -= 2;
		Bullet->Destroy();
	}

	if (OtherActor->IsA(ASpecialAttackBullet::StaticClass()))
	{
		ASpecialAttackBullet* SpecialAttackBullet = Cast<ASpecialAttackBullet>(OtherActor);
		EnemyHealth -= 20;
		
	}
}

void AEnemyCharacter::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

}


void AEnemyCharacter::MoveToTarget(AMainCharacter* MainCharacter)
{
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_MoveToTarget);

	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveToTarget()"));

		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(MainCharacter);
		MoveRequest.SetAcceptanceRadius(5.0f);

		FNavPathSharedPtr NavPath;

		AIController->MoveTo(MoveRequest, &NavPath);

		//Get som explaining T_T for TArray
		// FOR DEBUG
		//TArray<FNavPathPoint> PathPoints = NavPath->GetPathPoints();
		//for (auto Point : PathPoints) // give a point, which is a element in the arrays which is a PathPoint
		//{
		//	FVector Location = Point.Location;
		//	UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Red, 10.f, 1.5f);
		//}
	}
}


// ide for enemy collision mot bullet - bytte fra at bullet gjør dmg til at enemy collision tar dmg
