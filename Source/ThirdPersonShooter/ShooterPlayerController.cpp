// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No HUD class set."));
		return;
	}

	HUD = CreateWidget(this, HUDClass);
	HUD->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (!WinScreenClass || !LoseScreenClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No Win or Lost screen class set."));
		return;
	}

	HUD->RemoveFromViewport();

	UUserWidget* GameEndScreen = bIsWinner ? CreateWidget(this, WinScreenClass) : CreateWidget(this, LoseScreenClass);

	GameEndScreen->AddToViewport();

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestardDelay);
}

