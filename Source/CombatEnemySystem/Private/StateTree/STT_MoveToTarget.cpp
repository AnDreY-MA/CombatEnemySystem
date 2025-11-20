// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/STT_MoveToTarget.h"

#include "AIController.h"
#include "Tasks/AITask_MoveTo.h"

/*
EStateTreeRunStatus USTT_MoveToTarget::EnterState(FStateTreeExecutionContext& Context,
                                                  const FStateTreeTransitionResult& Transition)
{
	if(!ControllerContext->Implements<UEnemyControlInterface>()) return EStateTreeRunStatus::Failed;

	if(auto* TargetActor{IEnemyControlInterface::Execute_GetTargetActor(ControllerContext)}; TargetActor)
	{
		ControllerContext->SetFocus(TargetActor);
		auto* MoveTask {UAITask_MoveTo::AIMoveTo(ControllerContext, FVector::ZeroVector, TargetActor, AcceptanceRadius)};
		//MoveTask->
	}
	
	return Super::EnterState(Context, Transition);
}*/
