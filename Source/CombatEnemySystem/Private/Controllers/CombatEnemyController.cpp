// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CombatEnemyController.h"

#include "AbilitySystemComponent.h"
#include "LogCombatEnemySystem.h"
#include "Components/CombatEnemyStateComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Perception/AIPerceptionComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyController)


ACombatEnemyController::ACombatEnemyController(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer), TargetActor(nullptr), TargetContextQuery(nullptr)
{
	CombatStateComponent = CreateDefaultSubobject<UCombatEnemyStateComponent>("CombatStateComponent");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACombatEnemyController::OnPerceptionUpdated);

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
	UE_LOG(LogCombatEnemySystem, Warning, TEXT("Enemy = %f"), OnAttributeChangeData.NewValue);

	if(OnAttributeChangeData.NewValue == 0.0f)
	{
		auto* Own {GetPawn()};
		Own->Destroy();
		const float DestroyLife = FMath::RandRange(0.01f, 0.5f);
		Own->SetLifeSpan(DestroyLife);
		Own = nullptr;
	}

}

void ACombatEnemyController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogCombatEnemySystem, Warning, TEXT("DETECT"));
	if(Actor->GetClass() != GetPawn()->GetClass() && !TargetActor.IsValid())
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("DETECTSER %s"), *Actor->GetName());
		TargetActor = Actor;
		CombatStateComponent->DetectTarget();
	}

}