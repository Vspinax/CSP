// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"



void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}
	HUDOverlay->AddToViewport();

	// can be used to set In/visible from code
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	if (WPauseMenu)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WGameOverScreen)
	{
		GameOverScreen = CreateWidget<UUserWidget>(this, WGameOverScreen);
		if (GameOverScreen)
		{
			GameOverScreen->AddToViewport();
			GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WWinScreen)
	{
		WinScreen = CreateWidget<UUserWidget>(this, WWinScreen);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
			WinScreen->SetVisibility(ESlateVisibility::Hidden);
		}
	}
		
}
void AMainPlayerController::DisplayPauseMenu()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::RemovePauseMenu()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainPlayerController::TogglePauseMenu()
{
	if (bPauseMenuVisible)
	{
		RemovePauseMenu();
	}
	else
	{
		DisplayPauseMenu();
	}
}

void AMainPlayerController::DisplayGameOver()
{
	if (GameOverScreen)
	{
		bGameOverScreenVisible = true;
		GameOverScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::RemoveGameOver()
{
	if (GameOverScreen)
	{
		bGameOverScreenVisible = false;
		GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainPlayerController::ToggleGameOver()
{
	if (bGameOverScreenVisible)
	{
		RemoveGameOver();
	}
	else
	{
		DisplayGameOver();
	}
}

void AMainPlayerController::DisplayWin()
{
	if (WinScreen)
	{
		bWinScreenVisible = true;
		WinScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::RemoveWin()
{
	if (WinScreen)
	{
		bWinScreenVisible = false;
		WinScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainPlayerController::ToggleWinScreen()
{
	if (bWinScreenVisible)
	{
		RemoveWin();
	}
	else
	{
		DisplayWin();
	
	}
}
