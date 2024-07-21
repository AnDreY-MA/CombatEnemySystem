// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CombatEnemyDataAsset.h"

FPrimaryAssetId UCombatEnemyDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(DataType, GetFName());
}