// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_FindCompanions.generated.h"


UCLASS()
class COMBATENEMYSYSTEM_API UEQC_FindCompanions : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

	bool AlreadyTraceActor(const TArray<AActor*>& InTracedActors, const AActor& InActorCheck) const;
	
};