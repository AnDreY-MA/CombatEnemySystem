// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "StateTreeTaskBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STT_ReportTarget.generated.h"


class ACombatEnemyController;

USTRUCT()
struct FSTT_ReportInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<ACombatEnemyController> ControllerContext;
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<APawn> PawnContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, Category="Parameter")
	float Radius{1000.f};
	
	UPROPERTY(EditAnywhere, Category="Parameter")
	FGameplayTag ReportTag{FGameplayTag()};

	UPROPERTY(EditAnywhere, Category="Parameter")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditAnywhere, Category="Parameter")
	TEnumAsByte<EDrawDebugTrace::Type> DebugType {EDrawDebugTrace::None};
	
};


USTRUCT(DisplayName="Report")
struct COMBATENEMYSYSTEM_API FSTT_ReportTarget : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	explicit FSTT_ReportTarget();

	using FInstanceDataType = FSTT_ReportInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
							const FStateTreeTransitionResult& Transition) const override;

	const TArray<AActor*> GetActorsInRadius(const FStateTreeExecutionContext& Context) const;

};