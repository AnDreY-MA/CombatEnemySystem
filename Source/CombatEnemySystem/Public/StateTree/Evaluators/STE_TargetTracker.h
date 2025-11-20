#pragma once

#include "StateTreeAsyncExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "STE_TargetTracker.generated.h"

USTRUCT()
struct FSTE_TargetTrackerInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<const APawn> ContextPawn;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<const AActor> TargetActor{nullptr};
	
	UPROPERTY(EditAnywhere, Category="Output")
	double Distance{0.0};
	UPROPERTY(EditAnywhere, Category="Output")
	double DistanceSquared{0.0};

	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bDebug{false};
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Target Tracker"))
struct COMBATENEMYSYSTEM_API FSTT_TargetTracker : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTE_TargetTrackerInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const;

	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};