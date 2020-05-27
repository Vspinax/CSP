// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Bullet.h"
#include "Enemy.h"
#include "SpecialAttackBullet.h"
#include "MainPlayerController.h"
#include "CSPSaveGame.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/Decalcomponent.h"
#include "Materials/Material.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Boom (Pulls towards the player if theres Collision
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f; //Camera follows at this distance
	//CameraBoom->bUsePawnControlRotation = true; //Rotate arm based on Controller
	CameraBoom->RelativeRotation = FRotator(-50.f, 0.0f, 0.0f);

	//Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//Attaches the Camera at the end of the boom, and let the boom adjust to match the controller orientation.
	//FollowCamera->bUsePawnControlRotation = false;

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	//Hardcoded path
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	MaxHealth = 5;
	Health = 5;
	DeathCounter = 0;
	BossKill = 0;

	DashCooldown = 0.3f;
	DashAvailable = 0.f;
	DashTimer = 0.f;
	IsDashing = false;
	IsShootingSpecialAttack = false;
	SpecialAttackChargetime = 0.f;

	bESCDown = false;

}

// Called when the game starts or when spawned 
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Show system cursor. 
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	MainPlayerController = Cast<AMainPlayerController>(GetController());

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (BossKill >= 1)
	//{
	//	Win();
	//}

	DashAvailable += DeltaTime;
	DashTimer += DeltaTime;

	if (SpecialAttackChargetime <= SpecialAttackCooldown)
	{
		SpecialAttackChargetime += DeltaTime;
	}

	/// Move the cursor
	FHitResult Hit;
	bool HitResult = false;

	//The Cursor only Notices the world meshes
	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		///Updates cursor
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();

		///Set the new direction of the pawn:
		FVector CursorLocation = Hit.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit location %s!"), *Hit.Location.ToString());
		///Set Z to a little above ground
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

	
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
		CursorToWorld->SetWorldLocation(Hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);
	}

	if (IsShooting)
	{
		NextShot -= DeltaTime;
		if (NextShot <= 0.f)
		{
			Shoot();
			NextShot = ShootSpeed;
		}
	}
	else
	{
		NextShot = -0.1f;
	}


	if (IsDashing)
	{
		GetCharacterMovement()->MaxAcceleration = 100000.f;
		GetCharacterMovement()->MaxWalkSpeed = 1750.f;
		UE_LOG(LogTemp, Warning, TEXT("Before ac= %f"), GetCharacterMovement()->MaxAcceleration)
			UE_LOG(LogTemp, Warning, TEXT("Before speeed= %f"), GetCharacterMovement()->MaxWalkSpeed)

			if (DashTimer >= 0.2f) {
				// 2048 and 600 is the default 
			
				GetCharacterMovement()->MaxAcceleration = 2048.f;
				GetCharacterMovement()->MaxWalkSpeed = 600.f;
				UE_LOG(LogTemp, Warning, TEXT("after ac= %f"), GetCharacterMovement()->MaxAcceleration)
					UE_LOG(LogTemp, Warning, TEXT("after speeed= %f"), GetCharacterMovement()->MaxWalkSpeed)

			}


		DashAvailable = 0.f;

	}

	if (IsShootingSpecialAttack)
	{
		if (SpecialAttackChargetime >= SpecialAttackCooldown)
		{
			SpecialAttack();
			SpecialAttackChargetime = 0.f;
		}

		IsShootingSpecialAttack = false;
	}

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);

	PlayerInputComponent->BindAction("Refill", IE_Pressed, this, &AMainCharacter::Refill);

	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMainCharacter::ESCDown);
	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMainCharacter::ESCUp);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMainCharacter::StopShooting);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMainCharacter::StartDash);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &AMainCharacter::StopDash);

	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AMainCharacter::StartSpecialAttack);
	

}

bool AMainCharacter::CanMove(float Value)
{
	if (MainPlayerController) if (MainPlayerController->bGameOverScreenVisible) return false;
	if (MainPlayerController) if (MainPlayerController->bWinScreenVisible) return false;

	if (MainPlayerController) 
	{
		return((Controller != nullptr) && (Value != 0.0f)) &&
		!MainPlayerController->bPauseMenuVisible;
	}
	return false;
}

void AMainCharacter::MoveForward(float Value)
{
	if (CanMove(Value))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (CanMove(Value))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::Jump()
{
	if (MainPlayerController) if (MainPlayerController->bPauseMenuVisible) return;
	if (MainPlayerController) if (MainPlayerController->bGameOverScreenVisible) return;
	if (MainPlayerController) if (MainPlayerController->bWinScreenVisible) return;
	Super::Jump();
}

void AMainCharacter::Shoot()
{
	/*GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 150.f,
		GetActorRotation());*/

	// the number is the offsett of the bullet, the distance from the character where the  bullet will spawn

	FVector ShootingSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 50.f);
	FRotator ShootingSpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<ABullet>(BulletBlueprint, ShootingSpawnLocation, ShootingSpawnRotation);

}

void AMainCharacter::StartShooting()
{
	if (MainPlayerController) if (MainPlayerController->bPauseMenuVisible) return;
	if (MainPlayerController) if (MainPlayerController->bGameOverScreenVisible) return;
	if (MainPlayerController) if (MainPlayerController->bWinScreenVisible) return;

	IsShooting = true;


}

void AMainCharacter::StopShooting()
{
	IsShooting = false;
}

void AMainCharacter::TakeDamage()
{
	Health--;

	if (Health <= 0)
	{
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
		GameOver();
	}
}

void AMainCharacter::SpecialAttack()
{
	FVector ShootingSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 50.f);
	FRotator ShootingSpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<ASpecialAttackBullet>(SpecialAttackBulletBlueprint, ShootingSpawnLocation, ShootingSpawnRotation);
}

void AMainCharacter::StartSpecialAttack()
{
	if (MainPlayerController) if (MainPlayerController->bPauseMenuVisible) return;
	if (MainPlayerController) if (MainPlayerController->bGameOverScreenVisible) return;
	if (MainPlayerController) if (MainPlayerController->bWinScreenVisible) return;

	IsShootingSpecialAttack = true;
}

void AMainCharacter::Refill()
{
	//Cheats

	//if (MainPlayerController) if (MainPlayerController->bPauseMenuVisible) return;
	//if (MainPlayerController) if (MainPlayerController->bGameOverScreenVisible) return;
	//if (MainPlayerController) if (MainPlayerController->bWinScreenVisible) return;

	//Health = 5;
	//SpecialAttackChargetime = 10;
}

void AMainCharacter::ESCDown()
{
	bESCDown = true;

	if (MainPlayerController)
	{
		MainPlayerController->TogglePauseMenu();
	}
}

void AMainCharacter::ESCUp()
{
	bESCDown = false;
}

void AMainCharacter::GameOver()
{
	DeathCounter++;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);

	if (MainPlayerController)
	{
		MainPlayerController->ToggleGameOver();
	}
}

void AMainCharacter::Win()
{
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//if (MainPlayerController)
	//{
	//	MainPlayerController->ToggleWinScreen();
	//}
}

void AMainCharacter::SwitchLevel(FName LevelName)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentWorld = World->GetMapName();
		FName CurrentWorldName(*CurrentWorld);
		if (CurrentWorldName != LevelName)
		{
			UGameplayStatics::OpenLevel(World, LevelName);
		}
	}
}

void AMainCharacter::SaveGame()
{
	UCSPSaveGame* SaveGameInstance = Cast<UCSPSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSPSaveGame::StaticClass()));

	SaveGameInstance->CharacterStats.Location = GetActorLocation();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerName, SaveGameInstance->UserIndex);
}

void AMainCharacter::LoadGame()
{
	UCSPSaveGame* LoadGameInstance = Cast<UCSPSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSPSaveGame::StaticClass()));
	
	LoadGameInstance = Cast<UCSPSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));

	SetActorLocation(LoadGameInstance->CharacterStats.Location);

	Health = 5;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorHiddenInGame(false);

	if (MainPlayerController)
	{
		MainPlayerController->ToggleGameOver();
	}

}




void AMainCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor->IsA(AEnemy::StaticClass()))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Player Died"))
	//	OtherActor->Destroy();

	//	Hp--;

	//	if (Hp == 0)
	//	{
	//		Destroy();
	//	}
	//}
}

void AMainCharacter::StartDash()
{
	if (MainPlayerController) if (MainPlayerController->bPauseMenuVisible) return;
	if (MainPlayerController) if (MainPlayerController->bGameOverScreenVisible) return;
	if (MainPlayerController) if (MainPlayerController->bWinScreenVisible) return;

	if (DashAvailable > DashCooldown)
	{
		DashTimer = 0;
		IsDashing = true;
	}
}


void AMainCharacter::StopDash()
{

	GetCharacterMovement()->MaxAcceleration = 2048.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	IsDashing = false;
	DashTimer = 0.f;
}


