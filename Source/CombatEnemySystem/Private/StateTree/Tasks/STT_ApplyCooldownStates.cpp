// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_ApplyCooldownStates.h"

#include "LogCombatEnemySystem.h"
#include "StateTreeExecutionContext.h"
//#include "StateTree/Evaluators/STE_CooldownStates.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_ApplyCooldownStates)

FSTT_ApplyCooldownStates::FSTT_ApplyCooldownStates()
{
	bShouldCallTick = false;
	bShouldCopyBoundPropertiesOnTick = false;
#if WITH_EDITORONLY_DATA
	bConsideredForCompletion = false;
#endif
	
}

EStateTreeRunStatus FSTT_ApplyCooldownStates::EnterState(FStateTreeExecutionContext& Context,
                                                         const FStateTreeTransitionResult& Transition) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);
	
	if (!InstanceData.CooldownTracker.IsValid())
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("ApplyCooldownStates: CooldownTracker is not valid"));
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.CooldownTracker->UpdateCooldownState(InstanceData.NameState, false);
	
	return EStateTreeRunStatus::Running;
	
}
