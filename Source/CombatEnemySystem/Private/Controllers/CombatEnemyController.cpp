// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CombatEnemyController.h"

#include "Components/CombatEnemyStateComponent.h"
#include "Perception/AIPerceptionComponent.h"

ACombatEnemyController::ACombatEnemyController(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	CombatStateComponent = CreateDefaultSubobject<UCombatEnemyStateComponent>("CombatStateComponent");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACombatEnemyController::OnPerceptionUpdated);

	bStartAILogicOnPossess = true;
}

const AActor* ACombatEnemyController::GetTargetActor_Implementation() const
{
	return TargetActor.Get();
}

void ACombatEnemyController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor->GetClass() != GetPawn()->GetClass())
	{
		TargetActor = Actor;
		UE_LOG(LogTemp, Warning, TEXT("Detect"));
		CombatStateComponent->DetectTarget();
	}

}
