// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "ModularCharacter.h"
#include "CombatEnemyCharacter.generated.h"


UCLASS()
class COMBATENEMYSYSTEM_API ACombatEnemyCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void OnChangeAttribute(const FOnAttributeChangeData& OnAttributeChangeData);

private:
	UPROPERTY(EditDefaultsOnly, Category="CombatAbilities")
	FGameplayAttribute CombatAttribute;
	
};
