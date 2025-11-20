#pragma once

#include "StateTreeTaskBase.h"
#include "STT_GetRandomLocation.generated.h"

USTRUCT()
struct FSTT_GetRandomLocationInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Input")
	FVector OriginLocation {FVector::ZeroVector};
	UPROPERTY(EditAnywhere, Category="Input")
	float Radius {0.0f};

	UPROPERTY(EditAnywhere, Category="Output")
	FVector ResultLocation;
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Get Random Location"))
struct COMBATENEMYSYSTEM_API FSTT_GetRandomLocation : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_GetRandomLocationInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	
};