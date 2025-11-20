#include "StateTree/Tasks/STT_FireAttackBase.h"

#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"
#include "Components/DirectorCombatAIComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_FireAttackBase)

EStateTreeRunStatus FSTT_FireAttackBase::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	auto& InstanceData = Context.GetInstanceData(*this);
	auto* DirectorAI {UCombatAIFunctionLibrary::GetDirectorAI(Context.GetWorld())};
	if (!DirectorAI) return EStateTreeRunStatus::Failed;

	if (DirectorAI->ReserveLevelAttack(InstanceData.ControllerContext, InstanceData.LevelAttack) == false)
	{
		return EStateTreeRunStatus::Failed;
	}

	if (!CheckBlocking(InstanceData.PawnContext, InstanceData.TargetActor)) return EStateTreeRunStatus::Failed;
	
	
	return FStateTreeTaskCommonBase::EnterState(Context, Transition);
}

bool FSTT_FireAttackBase::CheckBlocking(ACharacter* InPawnContext, const AActor* TargetActor) const
{
	constexpr float HeightOffset {10.f};
	const FVector UpLocation {InPawnContext->GetActorUpVector() * HeightOffset};
	const FVector Start {InPawnContext->GetMesh()->GetSocketLocation("pelvis") + UpLocation};
	const FVector End {UpLocation + TargetActor->GetActorLocation()};
	const TArray<AActor*> IgnoreActors = {InPawnContext};
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingle(InPawnContext->GetWorld(), Start, End, TraceTypeQuery1,
		false, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor() == TargetActor)
		{
			return true;
		}
	}
	
	return false;

}