// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "TargetDetectCondition.generated.h"

class AAIController;


UCLASS()
class COMBATENEMYSYSTEM_API UTargetDetectCondition : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:
	explicit UTargetDetectCondition(const FObjectInitializer& Initializer = FObjectInitializer::Get());
	
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

private:
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AAIController> ContextController;
	UPROPERTY(EditAnywhere)
	bool bReverse;
	
};