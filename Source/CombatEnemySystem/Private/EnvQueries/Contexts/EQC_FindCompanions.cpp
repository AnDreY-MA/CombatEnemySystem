// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvQueries/Contexts/EQC_FindCompanions.h"

#include "Characters/CombatEnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EQC_FindCompanions)

void UEQC_FindCompanions::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	UObject* Owner = QueryInstance.Owner.Get();
	if (!IsValid(Owner)) return;

	const auto* OwnerCharacter = Cast<ACombatEnemyCharacter>(Owner);
	if (!IsValid(OwnerCharacter)) return;

	const FCollisionObjectQueryParams CollisionObjectParams = FCollisionObjectQueryParams(ECC_Pawn);

	FCollisionShape CollisionShape = FCollisionShape();
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(350.f);

	const FVector Start = OwnerCharacter->GetActorLocation();

	TArray<FHitResult> OutHits;
	TArray<AActor*> AllyCompanions;
	
	//DrawDebugSphere(GetWorld(), ((Start + FVector(150.f) - Start) / 2) + Start, 350.f, 10, FColor::Green, true);

	if (GetWorld()->SweepMultiByObjectType(OutHits, Start, Start+FVector(150.f), FQuat(), CollisionObjectParams, CollisionShape))
	{
		for (int32 HitIndex = 0; HitIndex < OutHits.Num(); HitIndex++)
		{
			ACombatEnemyCharacter* HitActor = Cast<ACombatEnemyCharacter>(OutHits[HitIndex].GetActor());
			if (!HitActor) continue;

			
			if (HitActor && HitActor!=OwnerCharacter && 
				OwnerCharacter->IsA(HitActor->GetClass()) && !AlreadyTraceActor(AllyCompanions,*HitActor))
			{
				AllyCompanions.Add(HitActor);
			}
		}
	}

	/*GLog->Log("Ally Companions found : " + FString::FromInt(AllyCompanions.Num() - 1));
	GLog->Log("Ally Companions of: " + OwnerCharacter->GetName());
	for (int32 i = 0; i < AllyCompanions.Num(); i++)
	{
		GLog->Log(AllyCompanions[i]->GetName());
	}*/

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, AllyCompanions);
	
}

bool UEQC_FindCompanions::AlreadyTraceActor(const TArray<AActor*>& InTracedActors, const AActor& InActorCheck) const
{
	for (int32 ActorIndex = 0; ActorIndex < InTracedActors.Num(); ActorIndex++)
	{
		if (InTracedActors[ActorIndex]->GetName() == InActorCheck.GetName())
		{
			return true;
		}
	}
	return false;
}