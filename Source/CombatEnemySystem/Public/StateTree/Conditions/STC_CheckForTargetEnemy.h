// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_CheckForTargetEnemy.generated.h"


class ACombatEnemyCharacter;

UCLASS()
class COMBATENEMYSYSTEM_API USTC_CheckForTargetEnemy : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const;


private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<ACombatEnemyCharacter> ContextCharacter;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere)
	bool bReverse{true};
	
};
