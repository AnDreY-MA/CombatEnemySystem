#pragma once 

#include "StateTreePropertyFunctionBase.h"
#include "StateTreeProperty_GetDistance.generated.h"

USTRUCT()
struct FSTTP_GetDistanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category="Context")
    TObjectPtr<const AActor> ContextActor;

    UPROPERTY(EditAnywhere, Category="Input")
    TObjectPtr<const AActor> TargetActor;

    UPROPERTY(EditAnywhere, Category="Output")
    float Output = 0.f;
};

USTRUCT(DisplayName="Get Distance")
struct FStateTreeProperty_GetDistance : public FStateTreePropertyFunctionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTTP_GetDistanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual void Execute(FStateTreeExecutionContext& Context) const override;
    
};