#include "StateTree/Tasks/STT_Reload.h"
#include "StateTreeExecutionContext.h"
#include "Interfaces/CombatEnemyInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_Reload)

FSTT_Reload::FSTT_Reload()
{
	bShouldCallTick = false;
	bShouldCallTickOnlyOnEvents = false;
	
}

EStateTreeRunStatus FSTT_Reload::EnterState(FStateTreeExecutionContext& Context,
                                            const FStateTreeTransitionResult& Transition) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);
	if (InstanceData.PawnContext->Implements<UCombatEnemyInterface>())
	{
		ICombatEnemyInterface::Execute_Reload(InstanceData.PawnContext);
		return EStateTreeRunStatus::Succeeded;
	}
	
	return EStateTreeRunStatus::Failed;

}