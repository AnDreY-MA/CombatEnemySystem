// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "CollisionQueryParams.h"
#include "Kismet/KismetSystemLibrary.h"

#include "STC_RangeAttackCanAttack.generated.h"

class AAIController;
class AActor;

UCLASS()
class COMBATENEMYSYSTEM_API USTC_RangeAttackCanAttack : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

private:
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AAIController> ControllerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere)
	FName TargetTag{ FName("Player") };

	UPROPERTY(EditAnywhere, Category = "Input|Trace")
	float Distance{ 200.f };

	UPROPERTY(EditAnywhere, Category = "Input|Trace")
	TEnumAsByte<ETraceTypeQuery> TraceChannel{ ECC_Visibility };

	UPROPERTY(EditAnywhere, Category = "Input|Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugTrace;
};
