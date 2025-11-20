// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_CheckChoosenState.generated.h"

/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API USTC_CheckChoosenState : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

public:
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	FName InputStateName;

	UPROPERTY(EditAnywhere)
	FName CompareName;
	
};
