#pragma once

#include "StateTreeTaskBase.h"
#include "STT_Reload.generated.h"

USTRUCT()
struct FSTT_ReloadInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<APawn> PawnContext;
	
};

USTRUCT(Category="Combat AI", DisplayName="Reload")
struct COMBATENEMYSYSTEM_API FSTT_Reload : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_ReloadInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	explicit FSTT_Reload();
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
							const FStateTreeTransitionResult& Transition) const override;
	
};