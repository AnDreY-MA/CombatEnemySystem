#include "StateTree/Tasks/STT_ThrowGrenade.h"

#include "AIController.h"
#include "StateTreeExecutionContext.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatEnemyInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_ThrowGrenade)

EStateTreeRunStatus FSTT_ThrowGrenade::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);

	if (!InstanceData.TargetActor) return EStateTreeRunStatus::Failed;

	InstanceData.ControllerContext->SetFocus(InstanceData.TargetActor);

	if (!InstanceData.CharacterContext->Implements<UCombatEnemyInterface>()) return EStateTreeRunStatus::Failed;
	
	ICombatEnemyInterface::Execute_ThrowGrenade(InstanceData.CharacterContext, InstanceData.TargetActor->GetActorLocation());
	return EStateTreeRunStatus::Succeeded;
	
}
