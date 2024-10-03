// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatEnemyStateComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyStateComponent)

UCombatEnemyStateComponent::UCombatEnemyStateComponent(const FObjectInitializer& InInitializer) :
	Super(InInitializer)
{
}

bool UCombatEnemyStateComponent::SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors)
{
	return Super::SetContextRequirements(Context, bLogErrors);
}

void UCombatEnemyStateComponent::DetectTarget(const AActor* InTarget)
{
	SendStateTreeEvent(DetectEvent);
	TargetActor = InTarget;

	GetWorld()->GetTimerManager().SetTimer(DistanceTimer, this, &UCombatEnemyStateComponent::CheckDistanceToTarget, IntervalCheckDistance, true);

}

void UCombatEnemyStateComponent::CheckDistanceToTarget()
{
	Distance = GetOwner()->GetDistanceTo(TargetActor.Get());
}