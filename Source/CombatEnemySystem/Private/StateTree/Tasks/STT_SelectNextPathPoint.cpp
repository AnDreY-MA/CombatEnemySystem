// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_SelectNextPathPoint.h"
#include "Controllers/CombatEnemyController.h"
#include <Actors/PathPoint.h>
#include <Components/PatrolerComponent.h>

#include "LogCombatEnemySystem.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_SelectNextPathPoint)

EStateTreeRunStatus USTT_SelectNextPathPoint::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	if (!PatrolComponent) EStateTreeRunStatus::Failed;
	PatrolComponent->SwapToNextPoint();

	return EStateTreeRunStatus::Succeeded;

}