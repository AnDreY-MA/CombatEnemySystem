// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatAIFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class EConsiderType : uint8
{
	FarBest = 0,
	CloseBest
};

class UDirectorCombatAIComponent;

UCLASS()
class COMBATENEMYSYSTEM_API UCombatAIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Combat AI | FunctionLibrary")
	[[nodiscard]] static bool IsTargetBehind(const AActor* InSourceActor, const AActor* InTargetActor);

	UFUNCTION(BlueprintPure, Category="Combat AI | FunctionLibrary")
	[[nodiscard]] static float GetAngleSightTarget(const AActor* InSourceActor, const AActor* InTargetActor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Combat AI | FunctionLibrary", meta=(WorldContext = "WorldContextObject"))
	[[nodiscard]] static UDirectorCombatAIComponent* GetDirectorAI(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="Combat AI | FunctionLibrary")
	[[nodiscard]] static float GetScoreByDistance(const FVector& InSourceLocation, const FVector& InTargetLocation, float InBestDistance, const EConsiderType InConsiderType = EConsiderType::CloseBest);

};