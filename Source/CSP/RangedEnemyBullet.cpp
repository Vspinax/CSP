// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyBullet.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"

// Sets default values
ARangedEnemyBullet::ARangedEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = RootSphere;

	RootSphere->SetGenerateOverlapEvents(true);
	RootSphere->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemyBullet::OnOverlap);
}

// Called when the game starts or when spawned
void ARangedEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARangedEnemyBullet::Tick(float DeltaTime)
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

void ARangedEnemyBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{

		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		MainCharacter->TakeDamage();

		//Destroy Bullet:
		Destroy();
	}

	if (OtherActor->IsA(ARangedEnemyBullet::StaticClass()))
	{

	}
	else
	{
		Destroy();
	}
}



