// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_CheckCanAttack.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API USTC_CheckCanAttack : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:
	explicit USTC_CheckCanAttack(const FObjectInitializer& Initializer = FObjectInitializer::Get());
	
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAIController> ControllerContext;

	UPROPERTY(EditAnywhere)
	bool bReverse;
	
};
