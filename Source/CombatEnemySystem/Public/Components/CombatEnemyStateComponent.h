// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "CombatEnemyStateComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=CombatAI, meta=(BlueprintSpawnableComponent))
class COMBATENEMYSYSTEM_API UCombatEnemyStateComponent : public UStateTreeComponent
{
	GENERATED_BODY()

public:
	explicit UCombatEnemyStateComponent(const FObjectInitializer& InInitializer = FObjectInitializer::Get());

	virtual bool SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors = false) override;
	 
	void DetectTarget(const AActor* InTarget);

	const float GetDistance() const { return Distance; }


private:
	void CheckDistanceToTarget();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="States|Events", meta=(AllowPrivateAccess=true))
	FStateTreeEvent DetectEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "States|Detect", meta = (AllowPrivateAccess = true))
	float IntervalCheckDistance{ 0.2f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States|DistanceChecking", meta = (AllowPrivateAccess = true))
	float Distance{ 0.0f };

	TWeakObjectPtr<const AActor> TargetActor;

	FTimerHandle DistanceTimer;
	
};