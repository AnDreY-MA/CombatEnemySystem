// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_SetFocusTarget.h"
#include "AIController.h"
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_SetFocusTarget)

EStateTreeRunStatus FSTT_SetFocusTarget::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    const auto& [ControllerContext, TargetActor] = Context.GetInstanceData(*this);
    if (!IsValid(ControllerContext) || !IsValid(TargetActor)) return EStateTreeRunStatus::Failed;
    
    ControllerContext->SetFocus(TargetActor);

    
    return EStateTreeRunStatus::Running;
}