// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	void PullTrigger();
	void Reload();
	int GetCurrentAmmo() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzeFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	float Range = 1000.f;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float DamageOutput = 10.f;

	UPROPERTY(VisibleAnywhere)
	int CurrentAmmo;

	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo = 10;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

	bool CheckIfAmmo() const;
};
