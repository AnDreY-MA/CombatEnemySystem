// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "Blueprint/UserWidget.h"
#include "CombatAIDebugWidget.generated.h"

class UTextBlock;

UCLASS()
class COMBATENEMYSYSTEM_API UCombatAIDebugWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTextCharacter(const FText& InText) const;
	void SetTextController(const FText& InText) const;
	void SetTasks(const FText& InText) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, MultiLine = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> AICharacter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, MultiLine = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> AIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, MultiLine = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Tasks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, MultiLine = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Scores;
	
};