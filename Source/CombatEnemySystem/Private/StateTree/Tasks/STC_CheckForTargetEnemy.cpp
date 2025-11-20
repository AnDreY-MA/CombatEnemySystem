// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Conditions/STC_CheckForTargetEnemy.h"

#include "Characters/CombatEnemyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

bool USTC_CheckForTargetEnemy::TestCondition(FStateTreeExecutionContext& Context) const
{
	if (!IsValid(TargetActor)) return false;
	
	const FVector& Start{ContextCharacter->GetActorLocation()};
	const FVector& End{TargetActor->GetActorLocation()};
	const TArray<AActor*> IgnoreActors{ContextCharacter.Get(), TargetActor.Get()};
	FHitResult HitResult;
	const bool bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceType, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);
	
	return bReverse ? !bResult : bResult;

}