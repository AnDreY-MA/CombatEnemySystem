#pragma once

#include "StateTreeTaskBase.h"
#include "STT_RequestAttack.generated.h"

class AAIController;

USTRUCT()
struct FSTT_RequestAttackInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<const AAIController> ControllerContext{nullptr};

	UPROPERTY(EditAnywhere, Category="Input")
	FGameplayTag LevelAttack = FGameplayTag();

	UPROPERTY(EditAnywhere)
	FStateTreeDelegateDispatcher OnSuccess;
	
	UPROPERTY(EditAnywhere)
	FStateTreeDelegateDispatcher OnFailed;
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Request Attack"))
struct COMBATENEMYSYSTEM_API FSTT_RequestAttack : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	explicit FSTT_RequestAttack();

	using FInstanceDataType = FSTT_RequestAttackInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
	                        const FStateTreeTransitionResult& Transition) const override;
	
};

USTRUCT()
struct FSTT_ReleaseAttackInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<const AAIController> ControllerContext{nullptr};

	UPROPERTY(EditAnywhere, Category="Input")
	FGameplayTag LevelAttack = FGameplayTag();

	UPROPERTY(EditAnywhere)
	FStateTreeDelegateListener OnReleaseReady;

	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Release Attack"))
struct COMBATENEMYSYSTEM_API FSTT_ReleaseAttack : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()
	
	explicit FSTT_ReleaseAttack();

	using FInstanceDataType = FSTT_ReleaseAttackInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
							const FStateTreeTransitionResult& Transition) const override;
	
};