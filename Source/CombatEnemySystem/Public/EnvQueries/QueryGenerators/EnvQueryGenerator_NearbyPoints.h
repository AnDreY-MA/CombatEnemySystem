// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_NearbyPoints.generated.h"

/**
 * 
 */
UCLASS()
class COMBATENEMYSYSTEM_API UEnvQueryGenerator_NearbyPoints : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

private:
	
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;
    
    UPROPERTY(EditAnywhere, Category = "NearbyPoints")
    float PointsDistance = 150.f;
    
    UPROPERTY(EditAnywhere, Category = "NearbyPoints")
    float DegreesGap = 60.f;

    UPROPERTY(EditAnywhere, Category = "NearbyPoints")
    float AngleStep = 20.f;

    UPROPERTY(EditAnywhere, Category = "NearbyPoints")
    float MaxRange = 500.f;
	
};
