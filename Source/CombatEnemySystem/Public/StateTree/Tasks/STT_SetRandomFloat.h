#pragma once

#include "StateTreeTaskBase.h"
#include "STT_SetRandomFloat.generated.h"

USTRUCT()
struct FSTT_SetRandomFloatInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Parameter")
	float MinValue = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	float MaxValue = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Output")
	float OutValue = 0.0f;
};

USTRUCT(Category="Common", meta=(DisplayName="Set Random Float"))
struct COMBATENEMYSYSTEM_API FSTT_SetRandomFloat : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	explicit FSTT_SetRandomFloat()
	{
		bShouldCallTick = 0;
	}

	using FInstanceDataType = FSTT_SetRandomFloatInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};