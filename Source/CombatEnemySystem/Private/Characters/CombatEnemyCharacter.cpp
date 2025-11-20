// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CombatEnemyCharacter.h"
#include "Components/GameFrameworkComponentManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/CombatStateComponentInterface.h>
#include <Components/CombatEnemyStateComponent.h>
#include "Components/PatrolerComponent.h"
#include "Controllers/CombatEnemyController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyCharacter)
	
ACombatEnemyCharacter::ACombatEnemyCharacter(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PatrolComponent = CreateDefaultSubobject<UPatrolerComponent>("PatrolComponent");
	
	/*DebugAIComponent = CreateDefaultSubobject<UCombatAIDebugComponent>("DebugAIComponent");
	DebugAIComponent->SetupAttachment(RootComponent);*/
	
}

void ACombatEnemyCharacter::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = GetData_Implementation().MovementSpeed;

	if (Controller && Controller->Implements<UCombatStateComponentInterface>())
	{
		auto* StateComponent = ICombatStateComponentInterface::Execute_GetCombatStateComponent(Controller);
		StateComponent->SetupStateTree(GetData_Implementation().StateTree);
	}

}

void ACombatEnemyCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);

}

void ACombatEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);

}

void ACombatEnemyCharacter::UnPossessed()
{
	Super::UnPossessed();

	if (OnDead.IsBound())
	{
		OnDead.Broadcast(this, GetController<ACombatEnemyController>());
	}
	
}

const FEnemyData ACombatEnemyCharacter::GetData_Implementation() const
{
	if (Data.IsNull())
	{
		const FEnemyData StatsInfo{};
		return StatsInfo;
	}

	const FEnemyData* Info = Data.GetRow<FEnemyData>("EnemyData");

	return *Info;

}

void ACombatEnemyCharacter::ChangeHealth(const float InHealthPercent) const
{
	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Execute(InHealthPercent);
	}

}

void ACombatEnemyCharacter::ChangeAmmo(const int32 InAmmoAmount) const
{
	if (OnWeaponAmmoChanged.IsBound())
	{
		OnWeaponAmmoChanged.Execute(InAmmoAmount);
	}
}

float ACombatEnemyCharacter::GetCrowdAgentMaxSpeed() const
{
	const float Speed = GetData_Implementation().MovementSpeed;
	return Speed;
}
