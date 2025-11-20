#pragma once

#include "StateTreeConsiderationBase.h"
#include "StateTreeConsiderationOwnerBehind.generated.h"

USTRUCT()
struct FStateTreeConsiderationOwnerBehindInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<const APawn> ContextPawn;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<const AActor> TargetActor;
	
};

USTRUCT(DisplayName="Owner Behind")
struct FStateTreeConsiderationOwnerBehind : public FStateTreeConsiderationCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeConsiderationOwnerBehindInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

protected:
	virtual float GetScore(FStateTreeExecutionContext& Context) const override;
	
};