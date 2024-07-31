// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyStateComponentInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyStateComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class COMBATENEMYSYSTEM_API IEnemyStateComponentInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Enemy State Component Interface")
	class UCombatEnemyStateComponent* GetEnemyStateComponent() const;
	
};