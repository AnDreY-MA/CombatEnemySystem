// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateTreeTaskBase.h"
#include "STT_SetFocusTarget.generated.h"

class AAIController;

USTRUCT()
struct FSTT_SetFocusTargetInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<AAIController> ControllerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AActor> TargetActor{nullptr};
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Set Focus Target"))
struct COMBATENEMYSYSTEM_API FSTT_SetFocusTarget : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	explicit FSTT_SetFocusTarget()
	{
		bShouldCallTick = 0;
	}

	using FInstanceDataType = FSTT_SetFocusTargetInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};