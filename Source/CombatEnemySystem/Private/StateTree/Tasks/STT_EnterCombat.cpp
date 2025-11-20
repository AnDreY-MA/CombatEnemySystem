#include "StateTree/Tasks/STT_EnterCombat.h"

#include "AIController.h"
#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"
#include "Components/DirectorCombatAIComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_EnterCombat)

EStateTreeRunStatus FSTT_EnterCombat::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const auto& [ControllerContext] = Context.GetInstanceData(*this);

	auto* DirectorAI {UCombatAIFunctionLibrary::GetDirectorAI(ControllerContext->GetWorld())};
	DirectorAI->RegisterActiveCombatEnemy(ControllerContext);

	return EStateTreeRunStatus::Running;
	
}