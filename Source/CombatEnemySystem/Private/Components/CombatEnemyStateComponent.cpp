// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatEnemyStateComponent.h"

#include "StateTreeExecutionContext.h"
#include "Components/StateTreeAIComponentSchema.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyStateComponent)

UCombatEnemyStateComponent::UCombatEnemyStateComponent(const FObjectInitializer& InInitializer) :
	Super(InInitializer)
{
	bStartLogicAutomatically = false;
}

void UCombatEnemyStateComponent::ReportEnemy()
{
	SendStateTreeEvent(ReportEvent);
}

void UCombatEnemyStateComponent::ReportInstigate()
{
	SendStateTreeEvent(ReportInstigateEvent);
}

void UCombatEnemyStateComponent::SetupStateTree(UStateTree* InTree, const bool InStart)
{
	if (!InTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("InTree is null, in StateComponent by Controller %s"), *GetOwner()->GetName());
		return;
	}

	StateTreeRef.SetStateTree(InTree);
	if (InStart)
	{
		StartLogic();
	}
}
