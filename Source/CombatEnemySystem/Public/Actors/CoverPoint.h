// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Engine/TargetPoint.h"
#include "Interfaces/DestinationActorInterface.h"
#include "CoverPoint.generated.h"

UCLASS()
class COMBATENEMYSYSTEM_API ACoverPoint : public ATargetPoint, public IDestinationActorInterface
{
	GENERATED_BODY()

public:
	// DestinationActorInterface Implementation
	virtual bool IsAvailable_Implementation() const override
	{
		return bReserved == false;
	}

	virtual bool Reserve_Implementation() override
	{
		if (bReserved == false)
		{
			bReserved = true;
			return true;
		}
		return false;
	}

	virtual void Release_Implementation() override
	{
		bReserved = false;
	}

	// End Implementation
	
private:
	UPROPERTY(VisibleAnywhere, Category="Cover Point")
	bool bReserved{false};
	
};