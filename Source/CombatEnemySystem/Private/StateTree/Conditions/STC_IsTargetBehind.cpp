#include "StateTree/Conditions/STC_IsTargetBehind.h"
#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_IsTargetBehind)

bool FSTC_IsTargetBehindCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const auto& [FromActor, ToActor, bRevert] = Context.GetInstanceData(*this);

	const bool bResult {UCombatAIFunctionLibrary::IsTargetBehind(FromActor, ToActor)};

	return bRevert ? !bResult : bResult;
	
}