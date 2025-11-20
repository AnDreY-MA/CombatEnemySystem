// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "GameplayTagContainer.h"

#include "STT_AreaTracker.generated.h"

class ACombatEnemyController;

UCLASS()
class COMBATENEMYSYSTEM_API USTT_AreaTracker : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	UFUNCTION()
	void DoTrace();

	void OnTraceDelegate(const FTraceHandle& InTraceHandle, FTraceDatum& InTraceDatum);

	UFUNCTION()
	void OnTrackedActorDestroyed(AActor* DestroyedActor);

private:
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<ACombatEnemyController> ControllerContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Output", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AActor> ActorTracked{ nullptr };

	UPROPERTY(EditAnywhere)
	FGameplayTag EventTracked;

	UPROPERTY(EditAnywhere)
	float CheckTraceInterval{ 0.4f };

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TraceChannel{ ECC_Visibility };

	UPROPERTY(EditAnywhere)
	float SphereRadius{ 300.f };

	UPROPERTY(EditAnywhere)
	bool bDebug{ false };

	UPROPERTY(EditAnywhere)
	float LifeTimeDebug{ 2.f };
	UPROPERTY()
	TWeakObjectPtr<const AActor> PawnContext;

	UPROPERTY()
	TWeakObjectPtr<UWorld> OwnerWorld;

	UPROPERTY()
	FTimerHandle TimerHandle;

	FTraceDelegate TraceDelegate;
	
};