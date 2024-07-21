// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyControlInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBATENEMYSYSTEM_API IEnemyControlInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="EnemyControlInterface")
	const AActor* GetTargetActor() const;
	
};