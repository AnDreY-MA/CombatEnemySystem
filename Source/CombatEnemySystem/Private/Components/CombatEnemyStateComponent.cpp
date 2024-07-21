// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatEnemyStateComponent.h"

UCombatEnemyStateComponent::UCombatEnemyStateComponent(const FObjectInitializer& InInitializer) :
	Super(InInitializer)
{
}

bool UCombatEnemyStateComponent::SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors)
{
	return Super::SetContextRequirements(Context, bLogErrors);
}

void UCombatEnemyStateComponent::DetectTarget()
{
	SendStateTreeEvent(DetectEvent);
}
