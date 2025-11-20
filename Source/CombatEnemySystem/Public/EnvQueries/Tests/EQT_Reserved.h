// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "EnvironmentQuery/EnvQueryTest.h"
#include "EQT_Reserved.generated.h"


UCLASS()
class COMBATENEMYSYSTEM_API UEQT_Reserved : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	explicit UEQT_Reserved(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};