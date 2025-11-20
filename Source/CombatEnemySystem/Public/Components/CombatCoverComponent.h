// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CombatCoverComponent.generated.h"

UENUM(BlueprintType)
enum class EHeightType : uint8
{
	None = 0,
	Top,
	Bottom
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCoverChanged, const bool, bCover, const EHeightType, HeightType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATENEMYSYSTEM_API UCombatCoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	explicit UCombatCoverComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintAssignable)
	FOnCoverChanged OnCoverChanged;

	UFUNCTION(BlueprintCallable, Category="Combat Cover Component")
	void UpdateCoverPoint(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="Combat Cover Component")
	void ReleaseCoverPoint();

private:
	UPROPERTY(VisibleAnywhere, Category="Combat Cover Component")
	TObjectPtr<UObject> CoverPoint;
		
};