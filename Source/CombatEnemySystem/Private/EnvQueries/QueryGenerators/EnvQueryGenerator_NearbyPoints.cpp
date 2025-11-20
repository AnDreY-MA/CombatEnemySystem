#include "EnvQueries/QueryGenerators/EnvQueryGenerator_NearbyPoints.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EnvQueryGenerator_NearbyPoints)

void UEnvQueryGenerator_NearbyPoints::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	Super::GenerateItems(QueryInstance);
	
	TArray<FNavLocation> LocationCandidates;

	const AActor* Pawn = Cast<AActor>((QueryInstance.Owner).Get());

	if (!IsValid(Pawn) || AngleStep <= 0) return;

	const FVector PawnLocation = Pawn->GetActorLocation();
	const FVector PawnForwardVector = Pawn->GetActorForwardVector();

	for (float Angle = DegreesGap; Angle < 360-DegreesGap; Angle += AngleStep)
	{
		const FVector RightVector = PawnForwardVector.RotateAngleAxis(Angle, FVector::UpVector);

		for (float Distance = PointsDistance; Distance < MaxRange; Distance += PointsDistance)
		{
			const FNavLocation NavLocation = FNavLocation(PawnLocation + RightVector * Distance);
			LocationCandidates.Add(NavLocation);
		}

	}

	ProjectAndFilterNavPoints(LocationCandidates, QueryInstance);
	StoreNavPoints(LocationCandidates, QueryInstance);
	
}