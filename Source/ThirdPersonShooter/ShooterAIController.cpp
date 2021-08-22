// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacterBase.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* EnemyPawn = GetPawn();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		if (EnemyPawn)
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacterBase* ControlledCharacter = Cast<AShooterCharacterBase>(GetPawn());

	if (ControlledCharacter)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}
