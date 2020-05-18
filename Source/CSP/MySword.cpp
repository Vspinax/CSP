// Fill out your copyright notice in the Description page of Project Settings.


#include "MySword.h"
#include "Enemy.h"
#include "RangedEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
AMySword::AMySword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    //RootSphere->SetupAttachment(GetRootComponent());
    RootComponent = RootSphere;

    //Mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Mesh"));
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootSphere);

    CollisionBox->SetGenerateOverlapEvents(true);
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMySword::OnOverlap);
    
}

// Called when the game starts or when spawned
void AMySword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySword::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
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

    if (OtherActor->IsA(ARangedEnemy::StaticClass()))
    {

        ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(OtherActor);
        RangedEnemy->RangedEnemyHealth -= 2;

        Destroy();
    }if (OtherActor->IsA(AEnemy::StaticClass()))
    {
        // Alternetivt : Cast<AEnemy>(OtherActor)->Hit(); 
        //Cast<AEnemy>(OtherActor)->Destroy();                  // Insta kill

        AEnemy* Enemy = Cast<AEnemy>(OtherActor);
        Enemy->EnemyHealth -= 2;

        //Destroy Bullet:
        Destroy();
    }

    if (OtherActor->IsA(ARangedEnemy::StaticClass()))
    {

        ARangedEnemy* RangedEnemy = Cast<ARangedEnemy>(OtherActor);
        RangedEnemy->RangedEnemyHealth -= 2;

        Destroy();
    }

    if (OtherActor != this)
    {
        Destroy();
    }
}