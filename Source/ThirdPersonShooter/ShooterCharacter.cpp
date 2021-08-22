// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ThirdPersonShooterGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("StopJumping"), IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AShooterCharacter::ReloadWeapon);
}

void AShooterCharacter::FireWeapon()
{
	Gun->PullTrigger();
}

void AShooterCharacter::ReloadWeapon()
{
	Gun->Reload();
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AShooterCharacter::IncreaseHealth(int Amount)
{
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + Amount);
}

float AShooterCharacter::GetHealthPercentage() const
{
	return CurrentHealth / MaxHealth;
}

int AShooterCharacter::GetCurrentAmmo() const
{
	return Gun->GetCurrentAmmo();
}

