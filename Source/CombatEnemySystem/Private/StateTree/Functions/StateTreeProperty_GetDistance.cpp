#include "StateTree/Functions/StateTreeProperty_GetDistance.h"
#include "StateTreeExecutionContext.h"

void FStateTreeProperty_GetDistance::Execute(FStateTreeExecutionContext& Context) const
{
	auto& [ContextActor, TargetActor, Output] = Context.GetInstanceData(*this);
	if (!ContextActor || !TargetActor) return;
	
	const float Distance = FVector::Dist(ContextActor->GetActorLocation(), TargetActor->GetActorLocation());
	Output = Distance;
}
