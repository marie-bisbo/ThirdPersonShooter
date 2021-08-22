// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacterBase.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AShooterCharacter : public AShooterCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FireWeapon();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void IncreaseHealth(int Amount);

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintPure)
	int GetCurrentAmmo() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void ReloadWeapon();
};
