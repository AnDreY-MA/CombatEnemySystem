// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_CheckRange.h"
#include "AIController.h"
#include "Components/CombatStateComponentInterface.h"
#include "Components/CombatEnemyStateComponent.h"

bool USTC_CheckRange::TestCondition(FStateTreeExecutionContext& InContext) const
{
	if (ControllerContext->Implements<UCombatStateComponentInterface>())
	{
		const float Distance{ ICombatStateComponentInterface::Execute_GetCombatStateComponent(ControllerContext)->GetDistance()};
		if (ConditionType == EConditionRangeType::LessEqual)
		{
			return Distance <= Range;
		}
		else if (ConditionType == EConditionRangeType::Equal)
		{
			return Distance == Range;
		}
		else if (ConditionType == EConditionRangeType::More)
		{
			return Distance > Range;
		}
		else if (ConditionType == EConditionRangeType::MoreEqual)
		{
			return Distance >= Range;
		}
		else
			return false;
	}
	return false;
}
