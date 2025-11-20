// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_RangeAttackCanAttack.h"
#include "AIController.h"
#include "GameFramework/Actor.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(STC_RangeAttackCanAttack)

bool USTC_RangeAttackCanAttack::TestCondition(FStateTreeExecutionContext& Context) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	AActor* Pawn = ControllerContext->GetPawn();

	const FVector Start{ Pawn->GetActorLocation() };
	const FVector End{ Start + Pawn->GetActorForwardVector() * Distance };

	const TArray<AActor*> IgnoreActors = { Pawn };


	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingle(Pawn->GetWorld(), Start, End, TraceChannel, true, IgnoreActors, DrawDebugTrace, HitResult, true))
	{
		const auto* HitActor{ HitResult.GetActor() };
		if (HitActor && HitActor->ActorHasTag(TargetTag))
		{
			return true;
		}
	}

	return false;

}