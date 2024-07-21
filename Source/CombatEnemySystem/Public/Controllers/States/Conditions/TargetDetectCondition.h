// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "TargetDetectCondition.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API UTargetDetectCondition : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Context")
	TObjectPtr<AAIController> ContextController;
	
};