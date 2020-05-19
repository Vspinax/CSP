// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Aim_cannon.h"

// Sets default values
AAim_cannon::AAim_cannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAim_cannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAim_cannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	SetActorLocation(NewLocation);

	

	if (TurnDelay < 240.f)
	{
		TurretMovement = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		TurretMovement.Normalize();
		SetActorRotation(TurretMovement.Rotation());

		TurnDelay++;
	}

	else if (TurnDelay < 480.f)
	{

		TurnDelay++;
	}

	else if (TurnDelay == 480.f)
	{
		TurnDelay = 0.f;
	}


}

