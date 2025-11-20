#include "StateTree/Tasks/STT_SetRandomFloat.h"
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_SetRandomFloat)

EStateTreeRunStatus FSTT_SetRandomFloat::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	if (Transition.ChangeType == EStateTreeStateChangeType::Changed)
	{
		auto& InstanceData = Context.GetInstanceData(*this);
		InstanceData.OutValue = FMath::RandRange(InstanceData.MinValue, InstanceData.MaxValue);
	}

	return EStateTreeRunStatus::Running;

}