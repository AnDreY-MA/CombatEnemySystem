#pragma once

#include "StateTreeTaskBase.h"
#include "STT_FireAttackBase.generated.h"

class AAIController;

USTRUCT()
struct FSTT_FireAttackBaseInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AAIController> ControllerContext;

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<ACharacter> PawnContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> TargetActor{nullptr};

	UPROPERTY(EditAnywhere, Category="Parameter")
	float AttackSpeed{0.f};
	UPROPERTY(EditAnywhere, Category="Parameter")
	FGameplayTag LevelAttack{FGameplayTag()};
	
};

USTRUCT()
struct COMBATENEMYSYSTEM_API FSTT_FireAttackBase : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_FireAttackBaseInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
							const FStateTreeTransitionResult& Transition) const override;

protected:
	bool CheckBlocking(ACharacter* InPawnContext, const AActor* TargetActor) const;

};