// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAIFunctionLibrary.h"

#include "LogCombatEnemySystem.h"
#include "Components/DirectorCombatAIComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatAIFunctionLibrary)

bool UCombatAIFunctionLibrary::IsTargetBehind(const AActor* InSourceActor, const AActor* InTargetActor)
{
	if (!IsValid(InSourceActor) || !IsValid(InTargetActor)) return false;
	
	FVector ToTarget {InTargetActor->GetActorLocation() - InSourceActor->GetActorLocation()};
	ToTarget.Normalize();

	const double Dot {FVector::DotProduct(InSourceActor->GetActorForwardVector(), ToTarget)};
	const bool bResult = Dot < 0.0;
	return bResult;
	
}

float UCombatAIFunctionLibrary::GetAngleSightTarget(const AActor* InSourceActor, const AActor* InTargetActor)
{
    	if (!InSourceActor || !InTargetActor) return 0.f;
    
    	const FVector TargetLocation = InTargetActor->GetActorLocation();
    	const FVector SourceLocation = InSourceActor->GetActorLocation();
    	
    	const FVector ToTarget = (SourceLocation - TargetLocation).GetSafeNormal2D();
    	const FVector ViewDir = InTargetActor->GetActorForwardVector().GetSafeNormal2D();
    
    	const float Dot = FVector::DotProduct(ViewDir, ToTarget);
    	const float CrossZ = FVector::CrossProduct(ViewDir, ToTarget).Z;
    
    	const float AngleRad = FMath::Atan2(CrossZ, Dot);

		const float AngleDeg = FMath::Abs(FMath::RadiansToDegrees(AngleRad));
    	
    	return AngleDeg;  
    	
}

UDirectorCombatAIComponent* UCombatAIFunctionLibrary::GetDirectorAI(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("WorldContextObject is not valid"));
		return nullptr;
	}
	
	const auto* GameMode {UGameplayStatics::GetGameMode(WorldContextObject)};
	if (!GameMode)
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("GameMode is not valid"));
		return nullptr;
	}

	if (GameMode->Implements<UDirectorCombatAIInterface>())
	{
		auto* DirectorAI {IDirectorCombatAIInterface::Execute_GetDirectorCombatAI(GameMode)};
		if (!DirectorAI)
		{
			UE_LOG(LogCombatEnemySystem, Warning, TEXT("DirectorAI is not valid"));
			return nullptr;
		}
		return DirectorAI;
	}
	
	return GameMode->FindComponentByClass<UDirectorCombatAIComponent>();
	
}

float UCombatAIFunctionLibrary::GetScoreByDistance(const FVector& InSourceLocation, const FVector& InTargetLocation,
	float InBestDistance, const EConsiderType InConsiderType)
{
	const float Distance = FVector::DistSquared(InSourceLocation, InTargetLocation);
	const float MaxSqr = FMath::Square(InBestDistance);

	if (InConsiderType == EConsiderType::CloseBest)
	{
		const float Score = FMath::Clamp(1.f - FMath::Abs(Distance - MaxSqr) / MaxSqr, 0.f, 1.f);
		return Score;
	}

	const float Score = FMath::Clamp(Distance / MaxSqr, 0.f, 1.f);

	return Score;
	/*const float Dist   = FVector::Dist(InSourceLocation, InTargetLocation);
	const float Delta  = (Dist - InBestDistance) / InBestDistance;
	const float Expon  = -0.5f * FMath::Square(Delta / 0.5);
	const float Score  = FMath::Exp(Expon);
	return FMath::Clamp(Score, 0.f, 1.f);*/
}