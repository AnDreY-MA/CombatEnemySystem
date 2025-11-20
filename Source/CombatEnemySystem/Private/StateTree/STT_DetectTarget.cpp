// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/STT_DetectTarget.h"
#include "Controllers/EnemyControlInterface.h"
#include "AIController.h"
#include "LogCombatEnemySystem.h"

EStateTreeRunStatus USTT_DetectTarget::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
    if (ContextController->Implements<UEnemyControlInterface>())
    {
        TargetActor = IEnemyControlInterface::Execute_GetTargetActor(ContextController);
        if (TargetActor)
        {
            UE_LOG(LogCombatEnemySystem, Display, TEXT("Detect Target = %s"), *TargetActor->GetName());
        }
    }
    FinishTask(true);

    return EStateTreeRunStatus();
}