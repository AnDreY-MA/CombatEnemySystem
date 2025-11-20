#include "StateTree/Tasks/STT_GetRandomLocation.h"
#include "StateTreeExecutionContext.h"
#include "NavigationSystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_GetRandomLocation)

EStateTreeRunStatus FSTT_GetRandomLocation::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	auto& InstanceData = Context.GetInstanceData(*this);
	FNavLocation ResultLocation;
	
	const bool bResult = UNavigationSystemV1::GetCurrent(Context.GetOwner()->GetWorld())->GetRandomReachablePointInRadius(InstanceData.OriginLocation, InstanceData.Radius, ResultLocation);
	InstanceData.ResultLocation = ResultLocation.Location;
	
	return bResult ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;

}