// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Evaluators/STE_Patrol.h"
#include <Components/PatrolerComponent.h>
#include "StateTreeExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STE_Patrol)


void FSTE__Patrol::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);

	auto& InstanceData = Context.GetInstanceData(*this);

	InstanceData.PatrolComponent = InstanceData.PawnContext->GetComponentByClass<UPatrolerComponent>();

}
