// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/States/Conditions/TargetDetectCondition.h"

#include "AIController.h"
#include "Controllers/EnemyControlInterface.h"

bool UTargetDetectCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	if(ContextController->Implements<UEnemyControlInterface>())
	{
		const auto* Target {IEnemyControlInterface::Execute_GetTargetActor(ContextController)};
		return IsValid(Target);
	}
	
	return false;

}