// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacterBase.h"
#include "AIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	AShooterCharacterBase* AIShooterCharacter =  Cast<AShooterCharacterBase>(AIPawn);

	if (!AIPawn || !AIShooterCharacter) return EBTNodeResult::Failed;

	AIShooterCharacter->FireWeapon();

	return EBTNodeResult::Succeeded;
}
