// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "StateTreeConditionBase.h"
#include "STC_CheckCanAttack.generated.h"

class AAIController;

USTRUCT()
struct FSTC_CanAttackInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Input")
	FGameplayTag LevelAttack = FGameplayTag();

	UPROPERTY(EditAnywhere)
	bool bReverse{false};
	
};

USTRUCT(Category = "Combat AI", meta = (DisplayName = "Can Attack"))
struct FSTC_CatAttack : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTC_CanAttackInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
};