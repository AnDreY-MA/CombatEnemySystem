// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatEnemyInterface.generated.h"


UINTERFACE(MinimalAPI)
class UCombatEnemyInterface : public UInterface
{
	GENERATED_BODY()
};


class COMBATENEMYSYSTEM_API ICombatEnemyInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Enemy Interface")
	bool CanThrowGrenade() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Enemy Interface")
	void ThrowGrenade(const FVector& InTargetLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Enemy Interface")
	bool IsInCover() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Enemy Interface")
	void StartFire(const FVector& InTargetLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Enemy Interface")
	void StopFiring();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Enemy Interface")
	void Reload();
	
	
};