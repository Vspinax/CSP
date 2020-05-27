// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSPSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		FVector Location;
};

/**
 * 
 */
UCLASS()
class CSP_API UCSPSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UCSPSaveGame();

	UPROPERTY(VisibleAnywhere, Category = "Basic")
		FString PlayerName;

		UPROPERTY(VisibleAnywhere, Category = "Basic")
		uint32 UserIndex;

		UPROPERTY(VisibleAnywhere, Category = "Basic")
		FCharacterStats CharacterStats;

};
