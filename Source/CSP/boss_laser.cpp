// Fill out your copyright notice in the Description page of Project Settings.


#include "boss_laser.h"

// Sets default values
Aboss_laser::Aboss_laser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aboss_laser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aboss_laser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

