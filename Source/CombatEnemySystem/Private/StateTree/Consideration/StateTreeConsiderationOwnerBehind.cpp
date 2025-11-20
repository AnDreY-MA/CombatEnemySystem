#include "StateTree/Consideration/StateTreeConsiderationOwnerBehind.h"

#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"

float FStateTreeConsiderationOwnerBehind::GetScore(FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);

	const bool bResult {UCombatAIFunctionLibrary::IsTargetBehind(InstanceData.TargetActor, InstanceData.ContextPawn)};

	return bResult ? 1.f : 0.0f;
	
}