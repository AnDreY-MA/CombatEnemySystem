// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_CheckCanAttack.h"

#include "AIController.h"
#include "LogCombatEnemySystem.h"
#include "Controllers/EnemyControlInterface.h"

USTC_CheckCanAttack::USTC_CheckCanAttack(const FObjectInitializer& Initializer) :
	Super(Initializer), bReverse(false)
{
}

bool USTC_CheckCanAttack::TestCondition(FStateTreeExecutionContext& Context) const
{
	if(ControllerContext && ControllerContext->Implements<UEnemyControlInterface>())
	{
		const bool bResult {IEnemyControlInterface::Execute_CanAttack(ControllerContext.Get())};
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("Can Attack = %d"), bResult);

		return bReverse ? !bResult : bResult;
	}
	UE_LOG(LogCombatEnemySystem, Warning, TEXT("Warn"));
	
	return Super::TestCondition(Context);

}