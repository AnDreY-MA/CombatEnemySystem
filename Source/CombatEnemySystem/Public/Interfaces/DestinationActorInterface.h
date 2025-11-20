// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestinationActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDestinationActorInterface : public UInterface
{
	GENERATED_BODY()
};


class COMBATENEMYSYSTEM_API IDestinationActorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Destination Actor Interface")
	bool IsAvailable() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Destination Actor Interface")
	bool Reserve();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Destination Actor Interface")
	void Release();
	
};