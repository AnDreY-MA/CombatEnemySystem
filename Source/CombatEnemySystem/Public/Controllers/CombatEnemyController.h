// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyControlInterface.h"
#include "ModularAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "CombatEnemyController.generated.h"

class UCombatEnemyStateComponent;
/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API ACombatEnemyController : public AModularAIController, public IEnemyControlInterface
{
	GENERATED_BODY()

public:
	
	explicit ACombatEnemyController(const FObjectInitializer& InObjectInitializer);

	virtual const AActor* GetTargetActor_Implementation() const override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CombatState", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCombatEnemyStateComponent> CombatStateComponent;

	UPROPERTY()
	TWeakObjectPtr<AActor> TargetActor;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
