// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CombatEnemyController.h"

#include "LogCombatEnemySystem.h"
#include "Components/CombatEnemyStateComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyController)

ACombatEnemyController::ACombatEnemyController(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent")), TargetActor(nullptr)
{
	CombatStateComponent = CreateDefaultSubobject<UCombatEnemyStateComponent>("CombatStateComponent");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");

	PerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSourceComponent");

	bStartAILogicOnPossess = true;
}

void ACombatEnemyController::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);

}

void ACombatEnemyController::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();

	if (auto* CrowdComponent{ Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()) }; CrowdComponent)
	{
		CrowdComponent->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		
		switch (AvoianceQulity)
		{
		case 1:
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;
		}

		CrowdComponent->SetAvoidanceGroup(1);
		CrowdComponent->SetGroupsToAvoid(1);
		CrowdComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}

}

void ACombatEnemyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

FGenericTeamId ACombatEnemyController::GetGenericTeamId() const
{
	return TeamId;
}

const AActor* ACombatEnemyController::GetTargetActor_Implementation() const
{
	return TargetActor.Get();

}