// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class ABullet;
class ASpecialAttackBullet;

UCLASS()
class CSP_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Controller")
	class AMainPlayerController* MainPlayerController;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Special Attack")
		float SpecialAttackCooldown = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Attack")
		float SpecialAttackChargetime;


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

	virtual void Jump() override;

	void Shoot();

	void StartShooting();

	void StopShooting();

	void TakeDamage();

	void SpecialAttack();

	void StartSpecialAttack();

	void Refill();

	// For Pause Menu

	bool bESCDown;

	void ESCDown();

	void ESCUp();

	bool CanMove(float Value);

	//Game Over

	void GameOver();

	//  SAVE/LOAD

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	//STATS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float DashCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float DashAvailable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat")
		float DashTimer;

	UPROPERTY()
		bool IsDashing;

private:

	///** Max Movementspeed of the Character*/
	//UPROPERTY(EditAnywhere, Category = "Pawn Setup")
	//	int Speed = 100;

	//a decal that projects teh cursor location
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Setup", meta = (AllowPrivateAccess = "true"))
		UDecalComponent* CursorToWorld;

	float ShootSpeed = 0.3f;

	float UpdateTime = 0.f;


	/**The bullet the pawn shoots*/
	UPROPERTY(EditAnywhere, Category = "Pawn Setup")
	TSubclassOf<ABullet> BulletBlueprint;

	UPROPERTY(EditAnywhere, Category = "Special Attack")
	TSubclassOf<ASpecialAttackBullet> SpecialAttackBulletBlueprint;

	bool IsShooting;

	bool IsShootingSpecialAttack;

	float NextShot = -0.1f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void StartDash();

	UFUNCTION()
		void StopDash();



};

//class Shooting{
//	bool ShootHold = false; //checks if you hold down the shoot button 
//	float ShootCooldown = 0.2; //minimum time between each bullet
//	float ShootTimer = 0; //current time on counter
//
//	void SpawnBullet() {
//		//this function should spawn the bullet, but I don't know the syntax 
//	}
//
//	void ShootRelease() {
//		ShootHold == false;
//	}
//
//	void ShootLoop() {
//		ShootHold == true;
//		while (ShootHold == true) {
//			if (ShootTimer == 0) {
//				SpawnBullet();
//				ShootTimer = ShootCooldown;
//				//insert syntax for waiting "ShootCooldown" seconds (0.2 seconds)
//				ShootTimer = 0;
//			}
//		}
//	}
//};