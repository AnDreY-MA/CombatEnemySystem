#pragma once 

#include "StateTreeConditionBase.h"
#include "STC_IsTargetBehind.generated.h"

USTRUCT()
struct FSTC_IsTargetBehindInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<const AActor> FromActor {nullptr};
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<const AActor> ToActor {nullptr};
    UPROPERTY(EditAnywhere)
    bool bRevert{false};
    
};

USTRUCT(Category = "Combat AI", meta = (DisplayName = "Is Target Behind"))
struct FSTC_IsTargetBehindCondition : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTC_IsTargetBehindInstanceData;

    virtual const UStruct* GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }
    
    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
    
};