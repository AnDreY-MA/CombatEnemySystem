// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CombatEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatEnemyCharacter)
	
ACombatEnemyCharacter::ACombatEnemyCharacter(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
{
	
}

void ACombatEnemyCharacter::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
	
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
