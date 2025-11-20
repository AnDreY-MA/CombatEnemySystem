#include "StateTree/Consideration/StateTreeDistanceConsideration.h"
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(StateTreeDistanceConsideration)

float FStateTreeDistanceConsideration::GetScore(FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);
	
	const float Distance = FVector::DistSquared(InstanceData.SourceLocation, InstanceData.TargetLocation);
	const float MaxSqr = FMath::Square(InstanceData.BestDistance);

	if (ConsiderType == EConsiderType::CloseBest)
	{
		const float Score = FMath::Clamp(1.f - FMath::Abs(Distance - MaxSqr) / MaxSqr, 0.f, 1.f);
		return Score;
	}

	const float Score = FMath::Clamp(Distance / MaxSqr, 0.f, 1.f);
	
	return Score;

}