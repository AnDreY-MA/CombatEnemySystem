#pragma once

#include "StateTreeEvaluatorBase.h"
#include "STE_StatsTracker.generated.h"

class ACombatEnemyCharacter;

USTRUCT()
struct FSTE_StatsTrackerInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<ACombatEnemyCharacter> ContextPawn;

	UPROPERTY(VisibleAnywhere, Category="Output")
	float MaxHealth{0.0f};

	UPROPERTY(VisibleAnywhere, Category="Output")
	float CurrentPercentHealth{1.f};

	UPROPERTY(VisibleAnywhere, Category="Output")
	float AttackSpeed{0.0f};

	UPROPERTY(VisibleAnywhere, Category="Output")
	FGameplayTag AttackLevel {FGameplayTag()};

	UPROPERTY(EditAnywhere, Category = "Output")
	float TimeAggression{ .0f };
	
	UPROPERTY(EditAnywhere, Category = "Output")
	float NormalNoise{ .0f };
	
	UPROPERTY(EditAnywhere, Category = "Output")
	float  HighNoise{ 0.f };

};

USTRUCT(Category="Combat AI", meta=(DisplayName="Stats Tracker"))
struct COMBATENEMYSYSTEM_API FSTE_StatsTracker : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FSTE_StatsTrackerInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
};