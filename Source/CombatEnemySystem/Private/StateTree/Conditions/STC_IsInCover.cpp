#include "StateTree/Conditions/STC_IsInCover.h"
#include "StateTreeExecutionContext.h"
#include "Interfaces/CombatEnemyInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_IsInCover)

bool FSTC_IsInCover::TestCondition(FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);

	if (InstanceData.ContextPawn->Implements<UCombatEnemyInterface>())
	{
		const bool bResult = ICombatEnemyInterface::Execute_IsInCover(InstanceData.ContextPawn);
		
		return InstanceData.bRevert ? !bResult : bResult;
	}

	return false;

}