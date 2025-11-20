// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STE_CooldownStates.generated.h"

UCLASS(meta = (DisplayName = "CooldownStates", Category = "Common"))
class COMBATENEMYSYSTEM_API USTT_CooldownStates : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	explicit USTT_CooldownStates(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void UpdateCooldownState(const FName& InNameState, const bool InValue);

	const bool IsAvailableState(const FName& InNameState) const;

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Output", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USTT_CooldownStates> CooldownTracker;

	UPROPERTY(EditAnywhere)
	TMap<FName, float> CooldownDefaults;

	UPROPERTY()
	TMap<FName, float> CooldownTimers;

	UPROPERTY()
	TMap<FName, bool> AvailableStates;
	
};