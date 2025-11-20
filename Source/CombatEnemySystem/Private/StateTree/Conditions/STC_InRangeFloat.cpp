#include "StateTree/Conditions/STC_InRangeFloat.h"
#include "Kismet/KismetMathLibrary.h"
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_InRangeFloat)

bool FSTC_InRangFloat::TestCondition(FStateTreeExecutionContext& Context) const
{
	const auto& [InputValue, ValueMin, ValueMax] = Context.GetInstanceData(*this);
	
	return UKismetMathLibrary::InRange_FloatFloat(InputValue, ValueMin, ValueMax);
	
}