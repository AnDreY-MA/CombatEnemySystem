#pragma once
#include "StateTreeConsiderationBase.h"
#include "Considerations/StateTreeCommonConsiderations.h"

#include "StateTreeConsiderationRangeAngleView.generated.h"

USTRUCT()
struct FConsiderationRangeAngleViewBehindInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<const APawn> ContextPawn;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<const AActor> TargetActor;

	UPROPERTY(EditAnywhere, Category="Parameter")
	float MaxAngleDegrees{45.f};
	UPROPERTY(EditAnywhere, Category="Parameter")
	FStateTreeConsiderationResponseCurve CurveResponse;
	
};

USTRUCT(DisplayName="Range Angle View")
struct FStateTreeConsiderationRangeAngleView : public FStateTreeConsiderationCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FConsiderationRangeAngleViewBehindInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

protected:
	virtual float GetScore(FStateTreeExecutionContext& Context) const override;
	
};
