#include "StateTree/Evaluators/STE_TargetTracker.h"

#include "LogCombatEnemySystem.h"
#include "StateTreeExecutionContext.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STE_TargetTracker)

EStateTreeRunStatus FSTT_TargetTracker::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.ContextPawn) || !IsValid(InstanceData.TargetActor))
		return EStateTreeRunStatus::Failed;
	
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSTT_TargetTracker::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	auto& InstanceData = Context.GetInstanceData(*this);

	if (!InstanceData.ContextPawn || !InstanceData.TargetActor)
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("ContextPawn or TargetActor is null"));
		return EStateTreeRunStatus::Failed;
	}

	const FVector PawnLocation = InstanceData.ContextPawn->GetActorLocation();
	const FVector TargetLocation = InstanceData.TargetActor->GetActorLocation();
	InstanceData.DistanceSquared = FVector::DistSquared(PawnLocation, TargetLocation);
	InstanceData.Distance = FMath::Sqrt(InstanceData.DistanceSquared);
	
	return EStateTreeRunStatus::Running;
}

void FSTT_TargetTracker::ExitState(FStateTreeExecutionContext& Context,
                                   const FStateTreeTransitionResult& Transition) const
{
	FStateTreeTaskCommonBase::ExitState(Context, Transition);
	
}