// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_MoveToTarget.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API USTT_MoveToTarget : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	explicit USTT_MoveToTarget(const FObjectInitializer& InInitializer = FObjectInitializer::Get());
	
	//virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat System", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AAIController> ControllerContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat System", meta=(AllowPrivateAccess="true"))
	float AcceptanceRadius;
	
};