// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterCharacter.h"

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthPack::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Cast<AShooterCharacter>(OtherActor))
	{
		IncreaseHealth(Cast<AShooterCharacter>(OtherActor), HealthAmount);
		Destroy();
	}
}

void AHealthPack::IncreaseHealth(AShooterCharacter* Player, int Amount)
{
	Player->IncreaseHealth(Amount);
}
