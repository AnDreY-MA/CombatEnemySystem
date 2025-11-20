#pragma once
#include "GameplayTagContainer.h"
#include "StateTreeEvaluatorBase.h"

#include "STE_Weapon.generated.h"

class ACombatEnemyCharacter;

USTRUCT()
struct FSTE_WeaponInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<ACombatEnemyCharacter> CharacterContext;

	UPROPERTY(EditAnywhere, Category="Output")
	int32 AmmoAmount{1};

	UPROPERTY(EditAnywhere, Category="Parameter")
	FGameplayTag EventAmmoEmpty{FGameplayTag()};
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Weapon Tracker"))
struct COMBATENEMYSYSTEM_API FSTE_Weapon : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTE_WeaponInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
};