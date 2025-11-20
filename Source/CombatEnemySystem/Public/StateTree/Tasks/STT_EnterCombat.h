#pragma once

#include "StateTreeTaskBase.h"
#include "STT_EnterCombat.generated.h"

class AAIController;

USTRUCT()
struct FSTT_EnterCombatInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AAIController> ControllerContext{nullptr};
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Enter Combat"))
struct COMBATENEMYSYSTEM_API FSTT_EnterCombat : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_EnterCombatInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};