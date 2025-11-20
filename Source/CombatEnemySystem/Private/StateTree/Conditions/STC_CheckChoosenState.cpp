// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_CheckChoosenState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_CheckChoosenState)

bool USTC_CheckChoosenState::TestCondition(FStateTreeExecutionContext& Context) const
{
	return InputStateName == CompareName;

}
