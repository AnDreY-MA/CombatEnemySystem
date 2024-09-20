// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/States/Conditions/TargetDetectCondition.h"

#include "AIController.h"
#include "Controllers/EnemyControlInterface.h"

UTargetDetectCondition::UTargetDetectCondition(const FObjectInitializer& Initializer) :
	Super(Initializer), bReverse(false)
{
}

bool UTargetDetectCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	if(ContextController->Implements<UEnemyControlInterface>())
	{
		const auto* Target {IEnemyControlInterface::Execute_GetTargetActor(ContextController.Get())};
		const bool bResult {IsValid(Target)};
		return bReverse ? !bResult : bResult;
	}
	
	return false;

}