// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CombatCoverComponent.h"

#include "LogCombatEnemySystem.h"
#include "Actors/CoverPoint.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatCoverComponent)

UCombatCoverComponent::UCombatCoverComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

void UCombatCoverComponent::UpdateCoverPoint(AActor* InActor)
{
	if (InActor->IsA(ACoverPoint::StaticClass()))
	{
		CoverPoint = InActor;

		const auto Message = IsValid(CoverPoint) ? CoverPoint->GetName() : "not valid";
		UE_LOG(LogCombatEnemySystem, Display, TEXT("Update Cover %s"), *Message);
	}
	
}

void UCombatCoverComponent::ReleaseCoverPoint()
{
	if (CoverPoint)
	{
		IDestinationActorInterface::Execute_Release(CoverPoint);
		CoverPoint = nullptr;
	}
	
}	