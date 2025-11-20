// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_ChangeMovementSpeed.h"
#include "Controllers/CombatEnemyController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EStateTreeRunStatus USTT_ChangeMovementSpeed::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	const auto* Character = ControllerContext->GetCharacter();
	Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
	
	return RunStatus;
}