// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CombatEnemyController.h"

#include "AbilitySystemComponent.h"
#include "LogCombatEnemySystem.h"
#include "Components/CombatEnemyStateComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyController)


ACombatEnemyController::ACombatEnemyController(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent")), TargetActor(nullptr), TargetContextQuery(nullptr)
{
	CombatStateComponent = CreateDefaultSubobject<UCombatEnemyStateComponent>("CombatStateComponent");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACombatEnemyController::OnPerceptionUpdated);

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

	if(auto* AbilityComponent{GetPawn()->FindComponentByClass<UAbilitySystemComponent>()}; AbilityComponent)
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(HealthAttribute).AddUObject(this, &ACombatEnemyController::OnChangeHealthAttribute);
	}

}

void ACombatEnemyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

AActor* ACombatEnemyController::GetTargetActor_Implementation() const
{
	return TargetActor.Get();
}

const UEnvQuery* ACombatEnemyController::GetQueryAroundTargetLocation_Implementation() const
{
	return TargetContextQuery.Get();
	
}

bool ACombatEnemyController::CanAttack_Implementation() const
{
	if(!OnPrepareAttack.IsBound())
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("OnPrepareAttack delegate haven't bound"));
		return false;
	}
	
	const bool bResult = OnPrepareAttack.Execute();
	return bResult;

}

void ACombatEnemyController::OnChangeHealthAttribute(const FOnAttributeChangeData& OnAttributeChangeData)
{
	UE_LOG(LogTemp, Warning, TEXT("DAMAGE"));
	if(OnAttributeChangeData.NewValue == 0.0f)
	{
			
	}

}

void ACombatEnemyController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor->GetClass() != GetPawn()->GetClass() && !TargetActor.IsValid())
	{
		UE_LOG(LogCombatEnemySystem, Display, TEXT("Detect %s by %s"), *Actor->GetName(), *GetPawn()->GetName());

		TargetActor = Actor;
		CombatStateComponent->DetectTarget(Actor);
	}

}