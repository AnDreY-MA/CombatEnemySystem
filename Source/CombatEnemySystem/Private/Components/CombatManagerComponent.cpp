// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatManagerComponent.h"

#include "LogCombatEnemySystem.h"
#include "Controllers/CombatEnemyController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatManagerComponent)

UCombatManagerComponent::UCombatManagerComponent(const FObjectInitializer& InInitializer) :
	Super(InInitializer), CombatAIControllerClass(ACombatEnemyController::StaticClass()), bAttacking(false)
{
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UCombatManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CombatAIControllerClass, OutControllers);

	for(auto* Controller : OutControllers)
	{
		if(auto* CombatController{Cast<ACombatEnemyController>(Controller)}; CombatController)
		{
			CombatController->OnPrepareAttack.BindDynamic(this, &UCombatManagerComponent::OnCheckAttackPrepared);

			ACharacter* AICharacter{CombatController->GetCharacter()};
			AICharacter->OnDestroyed.AddDynamic(this, &UCombatManagerComponent::OnDeadEnemyCharacter);
			AICharacters.Add(FName(AICharacter->GetName()));
		}
	}
	
}

bool UCombatManagerComponent::OnCheckAttackPrepared()
{
	return true;
}

void UCombatManagerComponent::OnDeadEnemyCharacter(AActor* DestroyedActor)
{
	UE_LOG(LogCombatEnemySystem, Display, TEXT("%s is dead"), *DestroyedActor->GetName());

	AICharacters.Remove(TArray<FName>::ElementType(DestroyedActor->GetName()));
	if(AICharacters.IsEmpty() && OnDeadAllEnemyCharacters.IsBound())
	{
		UE_LOG(LogCombatEnemySystem, Display, TEXT("All enemies is dead"));
		OnDeadAllEnemyCharacters.Broadcast();
	}

}