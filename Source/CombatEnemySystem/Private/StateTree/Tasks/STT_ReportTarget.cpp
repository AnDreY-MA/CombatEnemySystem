// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_ReportTarget.h"
#include "Controllers/CombatEnemyController.h"
#include "StateTreeExecutionContext.h"
#include "Characters/CombatEnemyCharacter.h"
#include "Components/CombatEnemyStateComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_ReportTarget)

DEFINE_LOG_CATEGORY_STATIC(STT_ReportTargetLog, All, All);

FSTT_ReportTarget::FSTT_ReportTarget()
{
	bShouldCallTick = 0;

}

EStateTreeRunStatus FSTT_ReportTarget::EnterState(FStateTreeExecutionContext& Context,
                                                  const FStateTreeTransitionResult& Transition) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);
	
	const TArray<AActor*> NearActors {GetActorsInRadius(Context)};
	if (NearActors.IsEmpty()) return EStateTreeRunStatus::Failed;

	const auto& InstanceData = Context.GetInstanceData(*this);

	for (const auto& Actor : NearActors)
	{
		if (!Actor) continue;
		
		if (auto* Controller{ Actor->GetInstigatorController() }; Controller && Controller->Implements<UCombatStateComponentInterface>())
		{
			if (InstanceData.TargetActor)
			{
				InstanceData.ControllerContext->UpdateTargetActor(InstanceData.TargetActor);
			}
			
			if (auto* StateComponent {ICombatStateComponentInterface::Execute_GetCombatStateComponent(Controller)}; StateComponent)
			{
				StateComponent->SendStateTreeEvent(InstanceData.ReportTag);
			}
		}
	}
	
	return EStateTreeRunStatus::Succeeded;
}

const TArray<AActor*> FSTT_ReportTarget::GetActorsInRadius(const FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);
	
	const FVector Location = InstanceData.PawnContext->GetActorLocation();

	const TArray<AActor*> IgnoreActors = { InstanceData.PawnContext };
	TArray<FHitResult> HitResults = {};
	TArray<AActor*> ResultActors = {};
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(Context.GetWorld(), Location, Location,
		InstanceData.Radius, InstanceData.ObjectTypes, false, IgnoreActors, InstanceData.DebugType, HitResults, true))
	{
		for (auto& Result : HitResults)
		{
			if (Result.GetActor()->IsA(ACombatEnemyCharacter::StaticClass()))
			{
				ResultActors.Add(Result.GetActor());
			}
		}
		return ResultActors;
	}

	return ResultActors;

}