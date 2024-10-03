// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_CheckRange.generated.h"

class AAIController;

UENUM(BlueprintType)
enum class EConditionRangeType : uint8
{
	Equal = 0,
	Less,
	More,
	LessEqual,
	MoreEqual
};

UCLASS()
class COMBATENEMYSYSTEM_API USTC_CheckRange : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAIController> ControllerContext;

	UPROPERTY(EditAnywhere)
	float Range{ 110.f };

	UPROPERTY(EditAnywhere)
	EConditionRangeType ConditionType{ EConditionRangeType::Equal };
	
};
