#pragma once

#include "StateTreeConditionBase.h"
#include "STC_CheckCooldownState.generated.h"

class USTT_CooldownStates;

USTRUCT()
struct FSTC_CheckCooldownInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName StateName{FName()};

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<USTT_CooldownStates> EvaluatorStates;
	
};

USTRUCT(DisplayName="Check Cooldown State")
struct FSTC_CheckCooldownState : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTC_CheckCooldownInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
};