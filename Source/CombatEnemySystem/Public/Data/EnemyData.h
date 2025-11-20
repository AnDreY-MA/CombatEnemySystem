// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

class UStateTree;

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	TObjectPtr<UStateTree> StateTree{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Behavior")
	FGameplayTag AttackLevel = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception", meta = (ClampMin = "0"))
	float TimeForAggresionSight{ 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception", meta = (ClampMin = "0", ClampMax = "1"))
	float NormalNoise{ 0.5f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception", meta = (ClampMin = "0", ClampMax = "1"))
	float HighNoise{ 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0", UIMin = "0"))
	float Health = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0", UIMin = "0"))
	float BasicAttackDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0", UIMin = "0"))
	float UltimateAttackDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float HitRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0", UIMin = "0"))
	float AttackSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0", UIMin = "0"))
	float MovementSpeed = 0.0f;

};