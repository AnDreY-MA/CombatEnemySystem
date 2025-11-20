// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateTreeEvaluatorBase.h"
#include "STE_Patrol.generated.h"

class ACombatEnemyController;
class APathPoint;
class UPatrolerComponent;

USTRUCT()
struct FSTE_PatrolInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<const AActor> PawnContext;

	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<UPatrolerComponent> PatrolComponent;
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Patrol"))
struct COMBATENEMYSYSTEM_API FSTE__Patrol : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FSTE_PatrolInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
};