// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateTreeTaskBase.h"
#include "STT_ClearFocusTarget.generated.h"

class AAIController;

USTRUCT()
struct FSTT_ClearFocusTargetInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<AAIController> ControllerContext;

};

USTRUCT(Category="Combat AI", meta=(DisplayName="Clear Focus Target"))
struct COMBATENEMYSYSTEM_API FSTT_ClearFocusTarget : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_ClearFocusTargetInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	
};