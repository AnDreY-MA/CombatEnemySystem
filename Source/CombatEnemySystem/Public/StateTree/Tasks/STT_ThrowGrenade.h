#pragma once

#include "StateTreeTaskBase.h"
#include "STT_ThrowGrenade.generated.h"

class ICombatEnemyInterface;
class AAIController;

USTRUCT()
struct FSTT_ThrowGrenadeInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AAIController> ControllerContext;
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<ACharacter> CharacterContext;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> TargetActor{nullptr};
	
};

USTRUCT(Category="Combat AI", meta=(DisplayName="Throw Grenade"))
struct COMBATENEMYSYSTEM_API FSTT_ThrowGrenade : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	explicit FSTT_ThrowGrenade()
	{
		bShouldCallTick = 0;
	}

	using FInstanceDataType = FSTT_ThrowGrenadeInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};