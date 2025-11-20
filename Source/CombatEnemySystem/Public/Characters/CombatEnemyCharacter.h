// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Data/EnemyDataInterface.h"
#include "Interfaces/CombatEnemyInterface.h"
#include "Data/EnemyData.h"
#include "Navigation/CrowdAgentInterface.h"
#include "CombatEnemyCharacter.generated.h"

class UCombatAIDebugComponent;
class UPatrolerComponent;
class ACombatEnemyController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDead, const ACombatEnemyCharacter*, EnemyCharacter, const ACombatEnemyController*, EnemyController);
DECLARE_DELEGATE_OneParam(FOnHealthChangedDelegate, const float);
DECLARE_DELEGATE_OneParam(OnWeaponAmmoChanged, const int32);


UCLASS()
class COMBATENEMYSYSTEM_API ACombatEnemyCharacter : public ACharacter, public IEnemyDataInterface, public ICombatEnemyInterface,
	public ICrowdAgentInterface
{
	GENERATED_BODY()

public:
	explicit ACombatEnemyCharacter(const FObjectInitializer& InInitializer = FObjectInitializer::Get());
	
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void UnPossessed() override;

	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

	/*StateTree evaluator delegate hook*/
	FOnHealthChangedDelegate OnHealthChanged;

	/*StateTree evaluator delegate hook. STE_Weapon*/
	OnWeaponAmmoChanged OnWeaponAmmoChanged;

	// ICrowdAgentInterface Implementation
	virtual FVector GetCrowdAgentLocation() const override { return GetActorLocation(); }

	virtual void GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const override
	{
		CylinderRadius = GetCapsuleComponent()->GetUnscaledCapsuleRadius();
		CylinderHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	}

	virtual float GetCrowdAgentMaxSpeed() const override;
	
	// End ICrowdAgentInterface

	virtual const FEnemyData GetData_Implementation() const override;

	// ICombatEnemyInterface Implementation
	virtual bool CanThrowGrenade_Implementation() const override { return false; }

	// End ICombatEnemyInterface

protected:
	/*Method for call OnHealthChanged from Blueprint Class*/
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void ChangeHealth(const float InHealthPercent) const;

	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void ChangeAmmo(const int32 InAmmoAmount) const;

private:
	UPROPERTY(EditAnywhere, Category = "Data", meta = (RowType = "/Script/CombatEnemySystem.EnemyData", DisplayPriority="-2"))
	FDataTableRowHandle Data;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patroler", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPatrolerComponent> PatrolComponent;
	
	/*UPROPERTY(EditDefaultsOnly, Category="Patroler")
	TObjectPtr<UCombatAIDebugComponent> DebugAIComponent;*/
	
};
