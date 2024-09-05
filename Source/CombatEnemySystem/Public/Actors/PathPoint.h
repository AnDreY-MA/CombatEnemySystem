// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PathPoint.generated.h"

UCLASS(Abstract, Category="MamontAISystem")
class COMBATENEMYSYSTEM_API APathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	explicit APathPoint(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE APathPoint* GetNextPathPoint() const { return NextPoint.Get(); }
	FORCEINLINE APathPoint* GetPreviousPathPoint() const { return PreviousPoint.Get();}

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PathPoint", meta=(AllowPrivateAccess="true"))
	TObjectPtr<APathPoint> NextPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PathPoint", meta=(AllowPrivateAccess="true"))
	TObjectPtr<APathPoint> PreviousPoint;
	
};