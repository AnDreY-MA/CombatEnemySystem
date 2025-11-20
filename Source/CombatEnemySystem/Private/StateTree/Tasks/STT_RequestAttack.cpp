#include "StateTree/Tasks/STT_RequestAttack.h"

#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"
#include "Components/DirectorCombatAIComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_RequestAttack)

FSTT_RequestAttack::FSTT_RequestAttack()
{
	bShouldCallTick = 0;
}

EStateTreeRunStatus FSTT_RequestAttack::EnterState(FStateTreeExecutionContext& Context,
                                                   const FStateTreeTransitionResult& Transition) const
{
	auto* DirectorAI {UCombatAIFunctionLibrary::GetDirectorAI(Context.GetOwner()->GetWorld())};
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const bool bResult {DirectorAI->ReserveLevelAttack(InstanceData.ControllerContext, InstanceData.LevelAttack)};

	return bResult ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
	
}

FSTT_ReleaseAttack::FSTT_ReleaseAttack()
{
	bShouldCallTick = 0;
}

EStateTreeRunStatus FSTT_ReleaseAttack::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	auto* DirectorAI {UCombatAIFunctionLibrary::GetDirectorAI(Context.GetOwner()->GetWorld())};
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	DirectorAI->ReleaseLevelAttack(InstanceData.ControllerContext, InstanceData.LevelAttack);
	
	return EStateTreeRunStatus::Succeeded;
	
}