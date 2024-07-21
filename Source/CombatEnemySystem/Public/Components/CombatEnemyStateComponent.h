// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "CombatEnemyStateComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API UCombatEnemyStateComponent : public UStateTreeComponent
{
	GENERATED_BODY()

public:
	explicit UCombatEnemyStateComponent(const FObjectInitializer& InInitializer);

	virtual bool SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors = false) override;

	
	void DetectTarget();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="States|Events", meta=(AllowPrivateAccess=true))
	FStateTreeEvent DetectEvent;

	
};