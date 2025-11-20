// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Evaluators/STE_DataTracker.h"
#include "Controllers/CombatEnemyController.h"
#include "Characters/CombatEnemyCharacter.h"
#include "Controllers/EnemyControlInterface.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STE_DataTracker)

void USTE_DataTracker::TreeStart(FStateTreeExecutionContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	Super::TreeStart(Context);

	ReceiveTreeStart();

}

void USTE_DataTracker::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	ActorLocation = ContextPawn->GetActorLocation();

	if (!TargetActor)
	{
		TargetActor = IEnemyControlInterface::Execute_GetTargetActor(ContextController);
	}

	if (TargetActor)
	{
		TargetLocation = TargetActor->GetActorLocation();
		DistanceToTarget = UKismetMathLibrary::Vector_Distance(ActorLocation, TargetLocation);
	}

	ReceiveTick(DeltaTime);
}

void USTE_DataTracker::TreeStop(FStateTreeExecutionContext& Context)
{
	ReceiveTreeStop();

}
