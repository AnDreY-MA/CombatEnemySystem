// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ActionEvent.generated.h"

class AAIController;
/**
 * 
 */
UCLASS(ClassGroup="CombatAI")
class COMBATENEMYSYSTEM_API UActionEvent : public UObject
{
	GENERATED_BODY()

public:
	explicit UActionEvent(const FObjectInitializer& InInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ActionEvent")
	void Execute();

private:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Info", meta=(AllowPrivateAccess="true"))
	FGameplayTag NameId;*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Info", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AAIController> Controller;

};