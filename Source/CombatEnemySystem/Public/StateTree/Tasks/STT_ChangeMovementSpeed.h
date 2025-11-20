// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_ChangeMovementSpeed.generated.h"

class ACombatEnemyController;

UCLASS()
class COMBATENEMYSYSTEM_API USTT_ChangeMovementSpeed : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr< ACombatEnemyController> ControllerContext;

	UPROPERTY(EditAnywhere)
	float Speed{ 300.f };

	UPROPERTY(EditAnywhere)
	EStateTreeRunStatus RunStatus{ EStateTreeRunStatus::Succeeded };
	
};