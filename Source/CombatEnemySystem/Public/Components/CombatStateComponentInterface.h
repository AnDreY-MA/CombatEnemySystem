// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatStateComponentInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatStateComponentInterface : public UInterface
{
	GENERATED_BODY()
};


class COMBATENEMYSYSTEM_API ICombatStateComponentInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat StateComponent Interface")
	class UCombatEnemyStateComponent* GetCombatStateComponent() const;

};