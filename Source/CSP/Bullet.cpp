
// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Enemy.h"
#include "EnemyCharacter.h"
#include "RangedEnemy.h"
#include "Components/SphereComponent.h"
#include "BossActorCode.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = RootSphere;

	RootSphere->SetGenerateOverlapEvents(true);
	RootSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
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

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    
    if (OtherActor->IsA(AEnemy::StaticClass()))
    {
        // Alternetivt : Cast<AEnemy>(OtherActor)->Hit(); 
        //Cast<AEnemy>(OtherActor)->Destroy();                  // Insta kill

        AEnemy* Enemy = Cast<AEnemy>(OtherActor);
        Enemy->EnemyHealth -= 2;

        //Destroy Bullet:
        Destroy();
    }

    else if (OtherActor->IsA(ARangedEnemy::StaticClass()))
    {

 /*       ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(OtherActor);
        RangedEnemy->RangedEnemyHealth -= 2;

        Destroy();*/
    }


     else if (OtherActor->IsA(AEnemyCharacter::StaticClass()))
    {
     
    }

     else if (OtherActor->IsA(ABossActorCode::StaticClass()))
    {

    }

    else if (OtherActor != this)
    {
        Destroy();
    }

}
