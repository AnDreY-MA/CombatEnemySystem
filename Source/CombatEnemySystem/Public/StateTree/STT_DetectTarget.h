// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_DetectTarget.generated.h"

class AAIController;

UCLASS()
class COMBATENEMYSYSTEM_API USTT_DetectTarget : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<const AAIController> ContextController;

	UPROPERTY(EditAnywhere)
	TObjectPtr<const AActor> TargetActor;
	
};
