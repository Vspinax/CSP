// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAttackBullet.h"
#include "Enemy.h"
#include "RangedEnemy.h"
#include "Components/SphereComponent.h"

// Sets default values
ASpecialAttackBullet::ASpecialAttackBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = RootSphere;

	RootSphere->SetGenerateOverlapEvents(true);
	RootSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpecialAttackBullet::OnOverlap);

}

// Called when the game starts or when spawned
void ASpecialAttackBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpecialAttackBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);

	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroyed)
	{
		this->Destroy();
	}

}

void ASpecialAttackBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		// Alternetivt : Cast<AEnemy>(OtherActor)->Hit(); 
		//Cast<AEnemy>(OtherActor)->Destroy();                  // Insta kill

		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		Enemy->EnemyHealth -= 20;

		//Destroy Bullet:
		//Destroy();
	}

	//if (OtherActor->IsA(ARangedEnemy::StaticClass()))
	//{

	//	ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(OtherActor);
	//	RangedEnemy->RangedEnemyHealth -= 20;

	//	//Destroy();
	//}
}

