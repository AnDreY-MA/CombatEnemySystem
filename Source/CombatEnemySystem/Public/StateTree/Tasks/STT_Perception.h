// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "GameplayTagContainer.h"
#include "StateTreePropertyRef.h"
#include "STT_Perception.generated.h"

class ACombatEnemyController;
class UAIPerceptionComponent;
class UAISense;

UCLASS()
class COMBATENEMYSYSTEM_API USTT_Perception : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	const TPair<bool, bool> CanSense(const FAIStimulus& InStimulus, const TSubclassOf<UAISense>& InCheckSenseClass) const;
	
	UFUNCTION()
	void SetAggresive(AActor* InActor);

	void CheckSight(AActor* InActor, const FAIStimulus& InStimulus);

	void HandleLostTarget(const AActor* InActor);
	void StartAggressive(AActor* InActor);

	void CheckHearing(const AActor* InActor, const FAIStimulus& InStimulus);

	void Clear();

	void SendEvent(const FGameplayTag& InEvent);

	// Used for if be report target from State Tree event
	UFUNCTION()
	void OnTargetUpdated(AActor* InTargetActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Context", meta = (AllowPrivateAccess="true"))
	TObjectPtr<ACombatEnemyController> ControllerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<const AActor> TargetActor{ nullptr };

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAISense> SightSenseClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAISense> HearSenseClass;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag Aggressive;
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag InstigateEvent;
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag SightDetectEvent;
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag HearDetectEvent;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag NormalInstigate;
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag HighInstigate;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float TimeAggresive{ 1.f };
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float HearStrenghtNormal{ 1.0f };
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float HearStrenghtHight{ 2.0f };
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	double MinDistanceForTimer{300.0};

	UPROPERTY(EditAnywhere, Category = "Output", meta=(AllowPrivateAccess="true"))
	FVector InstigateLocation;

	UPROPERTY(EditAnywhere, Category = "Output", meta=(AllowPrivateAccess="true"))
	bool bAggressive{ false };

	UPROPERTY(EditAnywhere, Category = "Output", meta=(AllowPrivateAccess="true"))
	FGameplayTag CurrentSense;

	UPROPERTY(EditAnywhere, Category = "Output", meta=(AllowPrivateAccess="true"))
	FGameplayTag TypeInstigate;
	
	UPROPERTY()
	TWeakObjectPtr<UAIPerceptionComponent> PerceptionComponent;

	FTimerHandle TimerDetection;

};