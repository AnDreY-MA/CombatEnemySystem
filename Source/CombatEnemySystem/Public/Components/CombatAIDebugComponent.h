// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/WidgetComponent.h"
#include "CombatAIDebugComponent.generated.h"


class UCombatAIDebugWidget;
class UStateTreeAIComponent;

UCLASS( ClassGroup=(CombatAI), meta=(BlueprintSpawnableComponent) )
class COMBATENEMYSYSTEM_API UCombatAIDebugComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:	
	explicit UCombatAIDebugComponent(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	void EnableDebug(const bool InbEnabled, const bool InbIsVisible);
	void StopDebug();
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool InitializeDebugWidget();

	void SetAgentDescription() const;

	void SetTasks() const;
	void SetScores() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Debug")
	bool bDebug{false};

	UPROPERTY()
	TObjectPtr<UCombatAIDebugWidget> DebugWidget;
	
	TWeakObjectPtr<UStateTreeAIComponent> StateTreeComponent;

};