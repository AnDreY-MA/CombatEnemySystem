#include "StateTree/Consideration/StateTreeConsiderationRangeAngleView.h"

#include "CombatAIFunctionLibrary.h"
#include "StateTreeExecutionContext.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(StateTreeConsiderationRangeAngleView)

DEFINE_LOG_CATEGORY_STATIC(LogConsiderationAngleView, All, All)

float FStateTreeConsiderationRangeAngleView::GetScore(FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);

	const FVector TargetLocation {InstanceData.TargetActor->GetActorLocation()};
	const FRotator TargetRotation {InstanceData.TargetActor->GetActorRotation()};
	const FVector ViewDirection = TargetRotation.Vector();

	const FVector OwnLocation {InstanceData.ContextPawn->GetActorLocation()};

	FVector ToEnemy = OwnLocation - TargetLocation;
	ToEnemy.Z = 0.f;
	ToEnemy.Normalize();

	const float CosAngle = FVector::DotProduct(ViewDirection, ToEnemy);
	const float CosThreshold = FMath::Cos(FMath::DegreesToRadians(InstanceData.MaxAngleDegrees));

	//const float Score = (1.f - CosAngle) / (1.f - CosThreshold);
	const float AngleDeg = UCombatAIFunctionLibrary::GetAngleSightTarget(InstanceData.TargetActor, InstanceData.ContextPawn);
	const float Normalized = FMath::Clamp(AngleDeg / InstanceData.MaxAngleDegrees, 0.f, 1.f);

	const float Score = FMath::Pow(Normalized, 1);

	//UE_LOG(LogConsiderationAngleView, Display, TEXT("STC_RangeAngleView score: %f"), Score);
	
	return Score;
	
}