// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/PathPoint.h"

#include "PatrolerComponent.generated.h"

class APathPoint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATENEMYSYSTEM_API UPatrolerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	explicit UPatrolerComponent(const FObjectInitializer& InInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintPure, Category = "Patrol")
	APathPoint* GetCurrentPoint() const { return CurrentPoint; }

	UFUNCTION(BlueprintPure, Category = "Patrol")
	const APathPoint* GetCurrentPoint_Const() const { return CurrentPoint; }

	UFUNCTION(BlueprintCallable, Category = "Patrol")
	void SetPoint(APathPoint* InPoint) { CurrentPoint = InPoint; }

	UFUNCTION(BlueprintCallable, Category = "Patrol")
	void SwapToNextPoint()
	{
		CurrentPoint = CurrentPoint->GetNextPathPoint_Implementation();
	}
		
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (AllowPrivateAccess="true"))
	TObjectPtr<APathPoint> CurrentPoint;

};
