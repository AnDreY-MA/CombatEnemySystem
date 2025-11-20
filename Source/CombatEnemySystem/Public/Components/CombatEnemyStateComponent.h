// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StateTreeAIComponent.h"
#include "CombatEnemyStateComponent.generated.h"


UCLASS(ClassGroup=CombatAI, meta=(BlueprintSpawnableComponent))
class COMBATENEMYSYSTEM_API UCombatEnemyStateComponent : public UStateTreeAIComponent
{
	GENERATED_BODY()

public:
	explicit UCombatEnemyStateComponent(const FObjectInitializer& InInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	void ReportEnemy();

	UFUNCTION(BlueprintCallable)
	void ReportInstigate();

	UFUNCTION(BlueprintCallable, Category = "Combat Enemy State Component")
	void SetupStateTree(UStateTree* InTree, const bool InStart = true);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "States|Events", meta = (AllowPrivateAccess = true))
	FStateTreeEvent ReportEvent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "States|Events", meta = (AllowPrivateAccess = true))
	FStateTreeEvent ReportInstigateEvent;

};