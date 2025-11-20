#include "StateTree/Conditions/STC_CheckCooldownState.h"
#include "LogCombatEnemySystem.h"
#include "StateTreeExecutionContext.h"
#include "StateTree/Evaluators/STE_CooldownStates.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_CheckCooldownState)

bool FSTC_CheckCooldownState::TestCondition(FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

	if (!InstanceData.EvaluatorStates)
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("CheckCooldown: EvaluatorStates is not valid"));
		return false;
	}
	
	return InstanceData.EvaluatorStates->IsAvailableState(InstanceData.StateName);
}