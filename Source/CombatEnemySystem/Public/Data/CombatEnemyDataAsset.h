// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatEnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API UCombatEnemyDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess="true"))
	FPrimaryAssetType DataType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Perception", meta=(AllowPrivateAccess="true"))
	float SightRadius{1500.f};
	
};