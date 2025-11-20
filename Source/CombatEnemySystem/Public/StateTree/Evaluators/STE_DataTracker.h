// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "STE_DataTracker.generated.h"

class ACombatEnemyController;
class ACombatEnemyCharacter;

UCLASS()
class COMBATENEMYSYSTEM_API USTE_DataTracker : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual void TreeStart(FStateTreeExecutionContext& Context) override;
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	virtual void TreeStop(FStateTreeExecutionContext& Context) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Context", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACombatEnemyController> ContextController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Context", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const ACombatEnemyCharacter> ContextPawn;

	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<const AActor> TargetActor;

	UPROPERTY(EditAnywhere, Category = "Output")
	FVector ActorLocation;
	UPROPERTY(EditAnywhere, Category = "Output")
	FVector TargetLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Output", meta = (AllowPrivateAccess="true"))
	float DistanceToTarget{0.0f};
	
};
