// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CombatEnemyCharacter.generated.h"


UCLASS()
class COMBATENEMYSYSTEM_API ACombatEnemyCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	explicit ACombatEnemyCharacter(const FObjectInitializer& InInitializer = FObjectInitializer::Get());
	
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual FGenericTeamId GetGenericTeamId() const override
	{ return FGenericTeamId(1); }
	
};