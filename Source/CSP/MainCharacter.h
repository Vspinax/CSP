// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class CSP_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	//Camera Boom positioning the camera behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//Base turn rates to scale turning functions for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// called for both forward and backward
	void MoveForward(float Value);

	//called for both right and left
	void MoveRight(float Value);


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	/**The max movement speed of the pawn*/
	UPROPERTY(EditAnywhere, Category = "Pawn Setup")
		int Speed = 100;

	/**The speed of pawn rotation*/
	UPROPERTY(EditAnywhere, Category = "Pawn Setup")
		float YawSpeed = 0.3f;

	//a decal that projects teh cursor location
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Setup", meta = (AllowPrivateAccess = "true"))
		UDecalComponent* CursorToWorld;

	/** The velocity of the pawn*/
	FVector CurrentVelocity;
};
