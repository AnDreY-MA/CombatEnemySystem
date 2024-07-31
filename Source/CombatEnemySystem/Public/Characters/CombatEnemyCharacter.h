// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Character.h"
#include "CombatEnemyCharacter.generated.h"


UCLASS()
class COMBATENEMYSYSTEM_API ACombatEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	explicit ACombatEnemyCharacter(const FObjectInitializer& InInitializer = FObjectInitializer::Get());
	
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};