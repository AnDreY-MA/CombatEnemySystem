#pragma once

#include "StateTreeConditionBase.h"
#include "STC_IsInCover.generated.h"

USTRUCT()
struct FSTC_IsInCoverInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<APawn> ContextPawn;
	
	UPROPERTY(EditAnywhere)
	bool bRevert{false};

};

USTRUCT(Category = "Combat AI", DisplayName="Is in Cover")
struct FSTC_IsInCover : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTC_IsInCoverInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
};