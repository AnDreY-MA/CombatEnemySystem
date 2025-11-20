// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_ClearFocusTarget.h"
#include "AIController.h"
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_ClearFocusTarget)

EStateTreeRunStatus FSTT_ClearFocusTarget::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const auto& [ControllerContext] = Context.GetInstanceData(*this);

	ControllerContext->ClearFocus(EAIFocusPriority::Gameplay);
	
	return EStateTreeRunStatus::Running;
	
}