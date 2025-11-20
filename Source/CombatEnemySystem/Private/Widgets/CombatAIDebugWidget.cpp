// Fill out your copyright notice in the Description page of Project Settings.
#include "Widgets/CombatAIDebugWidget.h"

#include "Components/TextBlock.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatAIDebugWidget)

void UCombatAIDebugWidget::SetTextCharacter(const FText& InText) const
{
	AICharacter->SetText(InText);

}

void UCombatAIDebugWidget::SetTextController(const FText& InText) const
{
	AIController->SetText(InText);

}

void UCombatAIDebugWidget::SetTasks(const FText& InText) const
{
	Tasks->SetText(InText);

}