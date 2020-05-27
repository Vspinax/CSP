// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetGenerateOverlapEvents(true);


}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		MainCharacter->SaveGame();
		UE_LOG(LogTemp, Warning, TEXT("Saved"));
	}
}

