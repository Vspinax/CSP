// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class CSP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    /**Speed of bullet*/
    UPROPERTY(EditAnywhere)
        float Speed = 400.f;

    /**Time before bullet selfdestruct*/
    UPROPERTY(EditAnywhere)
        float TimeBeforeDestroy = 5.f;

    float TimeLived{ 0 };

    /**The collision shape of the bullet*/
    UPROPERTY(EditAnywhere)
        class UShapeComponent* RootSphere = nullptr;


    UFUNCTION()
        void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);


};
