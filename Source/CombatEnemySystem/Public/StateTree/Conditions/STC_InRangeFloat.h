#pragma once
#include "StateTreeConditionBase.h"

#include "STC_InRangeFloat.generated.h"

USTRUCT()
struct FSTC_InRangFloatInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double InputValue{0.0};
	UPROPERTY(EditAnywhere)
	double ValueMin{0.0};
	UPROPERTY(EditAnywhere)
	double ValueMax{0.0};
};

USTRUCT(meta=(DisplayName="In Range Float"))
struct FSTC_InRangFloat : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTC_InRangFloatInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
    
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};
