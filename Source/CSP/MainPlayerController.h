// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CSP_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	//reference to the UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;
	
	//Variable to Hold the Widget after creating it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* HUDOverlay;

protected:
	virtual void BeginPlay() override;
};
