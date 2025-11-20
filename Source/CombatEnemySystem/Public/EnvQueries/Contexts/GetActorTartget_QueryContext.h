// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "GetActorTartget_QueryContext.generated.h"

UCLASS(DisplayName="ActorTarget")
class COMBATENEMYSYSTEM_API UEQC_ActorTarget : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	
};