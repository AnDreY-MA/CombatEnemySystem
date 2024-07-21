// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CombatEnemyCharacter.h"

#include "AbilitySystemComponent.h"

void ACombatEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(auto* AbilityComponent{FindComponentByClass<UAbilitySystemComponent>()}; AbilityComponent)
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(CombatAttribute).AddUObject(this, &ACombatEnemyCharacter::OnChangeAttribute);
	}
}

void ACombatEnemyCharacter::OnChangeAttribute(const FOnAttributeChangeData& OnAttributeChangeData)
{
}
