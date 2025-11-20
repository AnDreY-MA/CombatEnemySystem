// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyControlInterface.h"
#include "Perception/AIPerceptionTypes.h"
#include "Components/CombatStateComponentInterface.h"
#include "Data/EnemyDataInterface.h"
#include "Interfaces/CombatEnemyInterface.h"
#include "Navigation/CrowdAgentInterface.h"
#include "CombatEnemyController.generated.h"

class UCombatEnemyStateComponent;
class UAIPerceptionStimuliSourceComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyTargetUpdated, AActor*);

UCLASS(ClassGroup = "CombatAI", Blueprintable)
class COMBATENEMYSYSTEM_API ACombatEnemyController : public AAIController, public IEnemyControlInterface, public ICombatStateComponentInterface,
	public IEnemyDataInterface, public ICombatEnemyInterface
{
	GENERATED_BODY()

public:
	explicit ACombatEnemyController(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FOnEnemyTargetUpdated OnEnemyTargetUpdated;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void UpdateTargetActor(AActor* InActor)
	{
		TargetActor = InActor;
		if (OnEnemyTargetUpdated.IsBound())
		{
			OnEnemyTargetUpdated.Broadcast(InActor);
		}
	}


#pragma region Implementation Interfaces
	
	// IGenericTeamAgentInterface Implementation
	virtual FGenericTeamId GetGenericTeamId() const override;
	// IGenericTeamAgentInterface
	
	// IEnemyControlInterface Implementation
	virtual const AActor* GetTargetActor_Implementation() const override;

	// End

	// ICombatStateComponentInterface Implementation
	virtual UCombatEnemyStateComponent* GetCombatStateComponent_Implementation() override { return CombatStateComponent; }

	// End

	// IEnemyDataInterface Implementation
	virtual const FEnemyData GetData_Implementation() const override
	{
		if (const auto OwnPawn = GetPawn(); OwnPawn && OwnPawn->Implements<UEnemyDataInterface>())
		{
			return IEnemyDataInterface::Execute_GetData(OwnPawn);
		}
		
		return FEnemyData();
	}
	// End

	// ICombatEnemyInterface Implementation
	virtual bool CanThrowGrenade_Implementation() const override
	{
		if (const auto ControlledPawn = GetPawn(); IsValid(ControlledPawn))
		{
			return ICombatEnemyInterface::Execute_CanThrowGrenade(ControlledPawn);
		}
		return false;
	}

	// End ICombatEnemyInterface
#pragma endregion 
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<const AActor> TargetActor;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FGenericTeamId TeamId;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat|State", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCombatEnemyStateComponent> CombatStateComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat|State", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|CrowdAvoidance", meta = (AllowPrivateAccess = "true"))
	bool bEnableDetourCrowdAvoidance{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|CrowdAvoidance", meta = (AllowPrivateAccess = "true", EditCondition = "bEnableDetourCrowAvoidance", EditConditionHides, ClampMin = "1", ClampMax = "4"))
	int32 AvoianceQulity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|CrowdAvoidance", meta = (AllowPrivateAccess = "true", EditCondition = "bEnableDetourCrowAvoidance", EditConditionHides))
	float CollisionQueryRange{ 500.f };

};