#pragma once

#include "CombatAIFunctionLibrary.h"
#include "Considerations/StateTreeCommonConsiderations.h"
#include "StateTreeDistanceConsideration.generated.h"




USTRUCT()
struct FFStateTreeDistanceConsiderationInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	FVector SourceLocation{FVector::ZeroVector};

	UPROPERTY(EditAnywhere, Category = "Input")
	FVector TargetLocation{FVector::ZeroVector};

	UPROPERTY(EditAnywhere, Category = "Parameter")
	float BestDistance{0.0f};
	
};

USTRUCT(DisplayName="Distance")
struct FStateTreeDistanceConsideration : public FStateTreeConsiderationCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FFStateTreeDistanceConsiderationInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

protected:
	virtual float GetScore(FStateTreeExecutionContext& Context) const override;

private:
	UPROPERTY(EditAnywhere, Category="Default")
	EConsiderType ConsiderType = EConsiderType::FarBest;
	
};