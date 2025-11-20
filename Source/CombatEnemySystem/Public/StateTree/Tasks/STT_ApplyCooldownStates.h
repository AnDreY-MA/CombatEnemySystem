// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "StateTree/Evaluators/STE_CooldownStates.h"
#include "STT_ApplyCooldownStates.generated.h"

//class USTE_CooldownStates;

USTRUCT()
struct FSTT_ApplyCooldownStatesInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName NameState;

	UPROPERTY(EditAnywhere, Category="Input")
	TWeakObjectPtr<USTT_CooldownStates> CooldownTracker;
	
};

USTRUCT()
struct COMBATENEMYSYSTEM_API FSTT_ApplyCooldownStates : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_ApplyCooldownStatesInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	explicit FSTT_ApplyCooldownStates();

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};