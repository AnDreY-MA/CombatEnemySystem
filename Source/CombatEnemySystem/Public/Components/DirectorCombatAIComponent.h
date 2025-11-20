// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GameplayTagContainer.h"
#include "Characters/CombatEnemyCharacter.h"
#include "Components/ActorComponent.h"
#include "UObject/Interface.h"
#include "Components/CombatCoverComponent.h"
#include "DirectorCombatAIComponent.generated.h"

class AAIController;

UCLASS( ClassGroup=(CombatAI), BlueprintType, meta=(BlueprintSpawnableComponent) )
class COMBATENEMYSYSTEM_API UDirectorCombatAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	explicit UDirectorCombatAIComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void RegisterActiveCombatEnemy(AAIController* InController);

	int32 GetAmountActiveEnemies() const
	{
		return EnemyControllers.Num();
	}
	
	UFUNCTION(BlueprintCallable, Category="Combat AI|Director")
	bool ReserveLevelAttack(const AAIController* InController, const FGameplayTag& InLevel);
	UFUNCTION(BlueprintCallable, Category="Combat AI|Director")
	void ReleaseLevelAttack(const AAIController* InController, const FGameplayTag& InLevel);

#pragma region Control Attack Levels
	FORCEINLINE bool IsFreeAttackLevel(const FGameplayTag& InLevelCheck) const
	{
		const int32* CurrentPoints = CurrentAttackerLevels.Find(InLevelCheck);
		if (!CurrentPoints) return false;
		
		return *CurrentPoints != 0;
	}

	

#pragma endregion
	

#pragma region Control Target Actions

	UFUNCTION(BlueprintCallable, Category="Combat AI|Director")
	void AddPlayerAction(const FGameplayTag& InAction)
	{
		TargetActions.AddTag(InAction);
	}

	UFUNCTION(BlueprintCallable, Category="Combat AI|Director")
	void RemoveTargetAction(const FGameplayTag& InAction)
	{
		TargetActions.RemoveTag(InAction);
	}

	UFUNCTION(BlueprintCallable, Category="Combat AI|Director")
	bool HasTargetAction(const FGameplayTag& InAction) const
	{
		return TargetActions.HasTag(InAction);
	}
	
#pragma endregion

protected:
	virtual void BeginPlay() override;

private:
	void TriggerThrowGrenade();

	UFUNCTION()
	void StartTargetCoverTaked(const bool bIsCover, const EHeightType HeightType);

	UFUNCTION()
	void ApplyCoolDownGrenade();

	bool TryRequestThrowGrenade() const;

	bool CanReserveAttack(const AAIController* InController, const FGameplayTag& InLevel) const;

	UFUNCTION()
	void OnEnemyDead(const ACombatEnemyCharacter* EnemyCharacter, const ACombatEnemyController* EnemyController);

private:
	UPROPERTY(EditDefaultsOnly, Category="Combat AI")
	TMap<FGameplayTag, int32> DefaultAttackerLevels;
	
	UPROPERTY(EditDefaultsOnly, Category="Combat AI|Throw Grenade")
	FGameplayTag GrenadeEvent{FGameplayTag()};

	UPROPERTY(EditDefaultsOnly, Category="Combat AI|Throw Grenade")
	float TimeForGrenade{3.f};

	UPROPERTY(EditDefaultsOnly, Category="Combat AI|Throw Grenade")
	float GrenadeCooldown{5.f};
	UPROPERTY(EditDefaultsOnly, Category="Combat AI|Throw Grenade")
	bool bCanThrow{true};

	UPROPERTY(EditDefaultsOnly, Category="Combat AI|Log")
	bool bScreenLog{false};
	UPROPERTY(EditDefaultsOnly, Category="Combat AI|Log")
	bool bTextLog{false};

	UPROPERTY(VisibleAnywhere, Category="Combat AI", meta=(DisplayPriority="-1"))
	TMap<FGameplayTag, int32> CurrentAttackerLevels;

	UPROPERTY(VisibleAnywhere, Category="Combat AI")
	TArray<const AAIController*> EnemyControllers;
	
	UPROPERTY(Transient, VisibleAnywhere, Category="Combat AI")
	TSet<TWeakObjectPtr<const UObject>> ReserveHolders;

	UPROPERTY(VisibleAnywhere, Category="Combat AI")
	FGameplayTagContainer TargetActions;

	UPROPERTY(Transient)
	TWeakObjectPtr<const AActor> TargetActor{nullptr};
	
};

/*Interface*/

UINTERFACE(MinimalAPI)
class UDirectorCombatAIInterface : public UInterface
{
	GENERATED_BODY()
};

class COMBATENEMYSYSTEM_API IDirectorCombatAIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CombatAI|Director Interface")
	UDirectorCombatAIComponent* GetDirectorCombatAI() const;
	
};