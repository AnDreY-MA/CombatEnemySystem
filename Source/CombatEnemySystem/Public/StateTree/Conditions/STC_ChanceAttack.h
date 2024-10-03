// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_ChanceAttack.generated.h"


UCLASS()
class COMBATENEMYSYSTEM_API USTC_ChanceAttack : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", AllowPrivateAccess = "true"))
	float ChanceMin{ 0.65f };
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0",  AllowPrivateAccess = "true"))
	float ChanceMax{ 0.75f };
};
