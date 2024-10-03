// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AttributeSet.h"
#include "EnemyControlInterface.h"
#include "GameplayEffectTypes.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "Perception/AIPerceptionTypes.h"
#include "Components/CombatStateComponentInterface.h"
#include "CombatEnemyController.generated.h"

class UCombatEnemyStateComponent;
class UAIPerceptionStimuliSourceComponent;

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnPrepareAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, ACharacter* const , CharacterActor);

UCLASS(ClassGroup = "CombatAI", Abstract, Blueprintable)
class COMBATENEMYSYSTEM_API ACombatEnemyController : public AAIController, public IEnemyControlInterface, public ICombatStateComponentInterface
{
	GENERATED_BODY()

public:
	
	explicit ACombatEnemyController(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	FOnPrepareAttack OnPrepareAttack;

	UPROPERTY()
	FOnAttack OnAttack;

	UPROPERTY()
	FOnDead OnDead;
	
	// IGenericTeamAgentInterface Implementation
	virtual FGenericTeamId GetGenericTeamId() const override
	 {return FGenericTeamId(1);}
	
	// IEnemyControlInterface Implementation
	virtual AActor* GetTargetActor_Implementation() const override;

	virtual const UEnvQuery* GetQueryAroundTargetLocation_Implementation() const override;

	virtual bool CanAttack_Implementation() const override;

	// End

	// ICombatStateComponentInterface Implementation
	virtual UCombatEnemyStateComponent* GetCombatStateComponent_Implementation() const override 
	{
		return CombatStateComponent;
	}

	// End

private:
	void OnChangeHealthAttribute(const FOnAttributeChangeData& OnAttributeChangeData);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<AActor> TargetActor;

	UPROPERTY(EditDefaultsOnly, Category="Combat|Ability System")
	FGameplayAttribute HealthAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat|State", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCombatEnemyStateComponent> CombatStateComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat|State", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSource;

	UPROPERTY(EditDefaultsOnly, Category="EQS")
	TObjectPtr<UEnvQuery> TargetContextQuery;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};