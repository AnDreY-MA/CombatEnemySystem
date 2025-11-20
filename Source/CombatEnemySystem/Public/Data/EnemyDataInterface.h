// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/EnemyData.h"
#include "EnemyDataInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyDataInterface : public UInterface
{
	GENERATED_BODY()
};


class COMBATENEMYSYSTEM_API IEnemyDataInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Enemy Data Interface")
	const FEnemyData GetData() const;

};
