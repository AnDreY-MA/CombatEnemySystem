// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_CheckCanAttack.h"

#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"
#include "Components/DirectorCombatAIComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_CheckCanAttack)


bool FSTC_CatAttack::TestCondition(FStateTreeExecutionContext& Context) const
{
	const auto* DirectorAI {UCombatAIFunctionLibrary::GetDirectorAI(Context.GetOwner()->GetWorld())};
	if (!DirectorAI) return false;

	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const bool bResult {DirectorAI->IsFreeAttackLevel(InstanceData.LevelAttack)};
	
	return InstanceData.bReverse ? !bResult : bResult;
	
}