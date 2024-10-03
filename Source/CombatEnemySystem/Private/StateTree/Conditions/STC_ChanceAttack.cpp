// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_ChanceAttack.h"
#include "Kismet/KismetMathLibrary.h"

bool USTC_ChanceAttack::TestCondition(FStateTreeExecutionContext& Context) const
{
    const bool bResult = UKismetMathLibrary::RandomBoolWithWeight(UKismetMathLibrary::RandomFloatInRange(ChanceMin, ChanceMax));
    return bResult;
}