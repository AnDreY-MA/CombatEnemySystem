// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_MoveToTarget.generated.h"

class ACombatEnemyController;

UCLASS()
class COMBATENEMYSYSTEM_API USTT_MoveToTarget : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	//virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Context", meta=(AllowPrivateAccess="true"))
	TObjectPtr<ACombatEnemyController> ControllerContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> Target;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat System", meta=(AllowPrivateAccess="true"))
	float AcceptanceRadius;
	
};