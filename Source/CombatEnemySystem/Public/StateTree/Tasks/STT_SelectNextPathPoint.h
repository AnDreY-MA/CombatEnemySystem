// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_SelectNextPathPoint.generated.h"

class ACombatEnemyController;
class APathPoint;
class UPatrolerComponent;


UCLASS()
class COMBATENEMYSYSTEM_API USTT_SelectNextPathPoint : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<ACombatEnemyController> ControllerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UPatrolerComponent> PatrolComponent;

};
