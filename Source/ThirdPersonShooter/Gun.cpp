// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void AGun::PullTrigger()
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return;

	if (!CheckIfAmmo()) return;

	if (CurrentAmmo > 0)
		--CurrentAmmo;

	UGameplayStatics::SpawnEmitterAttached(MuzzeFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bHitSuccessful = GunTrace(Hit, ShotDirection);

	if (bHitSuccessful)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

		AActor* ActorHit = Hit.GetActor();
		if (ActorHit)
		{
			FPointDamageEvent DamageEvent(DamageOutput, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(DamageOutput, DamageEvent, OwnerController, this);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FVector OwnerLocation;
	FRotator OwnerRotation;
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) { return false; }

	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);
	ShotDirection = -OwnerRotation.Vector();

	FVector EndPoint = OwnerLocation + OwnerRotation.Vector() * Range;

	FCollisionQueryParams Paramaters;
	Paramaters.AddIgnoredActor(this);
	Paramaters.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, OwnerLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Paramaters);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return nullptr; };

	return OwnerPawn->GetController();
}

bool AGun::CheckIfAmmo() const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* OwnerController = OwnerPawn->GetController();

	if (!OwnerPawn || !OwnerController) { return false; }
	if (CurrentAmmo == 0 && OwnerPawn == PlayerPawn) { return false; }

	return true;
}

void AGun::Reload()
{
	CurrentAmmo = MaxAmmo;
}

int AGun::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

