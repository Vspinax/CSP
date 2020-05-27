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

	//PAUSE MENU

	//reference to the UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;
	
	//Variable to Hold the Widget after creating it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WPauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* PauseMenu;

	bool bPauseMenuVisible;

	UFUNCTION(BlueprintCallable)
	void DisplayPauseMenu();

	UFUNCTION(BlueprintCallable)
	void RemovePauseMenu();

	void TogglePauseMenu();

	//GAME OVER SCREEN


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UUserWidget> WGameOverScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UUserWidget* GameOverScreen;

	bool bGameOverScreenVisible;

	UFUNCTION(BlueprintCallable)
		void DisplayGameOver();

	UFUNCTION(BlueprintCallable)
		void RemoveGameOver();

	void ToggleGameOver();

	//Win Screen

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UUserWidget> WWinScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UUserWidget* WinScreen;

	bool bWinScreenVisible;

	UFUNCTION(BlueprintCallable)
		void DisplayWin();

	UFUNCTION(BlueprintCallable)
		void RemoveWin();

	void ToggleWinScreen();


protected:
	virtual void BeginPlay() override;
};
