// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "PathPoint.generated.h"

UINTERFACE(MinimalAPI)
class UPathPointInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class COMBATENEMYSYSTEM_API IPathPointInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Path Point Interface")
	class APathPoint* GetNextPathPoint() const;

};

UCLASS(Abstract, Category="MamontAISystem")
class COMBATENEMYSYSTEM_API APathPoint : public AActor, public IPathPointInterface
{
	GENERATED_BODY()
	
public:	
	explicit APathPoint(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	APathPoint* GetNextPathPoint_Implementation() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PathPoint", meta=(AllowPrivateAccess="true"))
	TObjectPtr<APathPoint> NextPoint;
	
};