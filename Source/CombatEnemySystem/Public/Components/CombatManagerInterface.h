// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCombatManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBATENEMYSYSTEM_API ICombatManagerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Combat Manager Interface")
	class UCombatManagerComponent* GetCombatManagerComponent() const;
	
};