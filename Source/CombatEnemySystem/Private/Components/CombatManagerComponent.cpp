// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatManagerComponent.h"

#include "Controllers/CombatEnemyController.h"
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
			CombatController->OnDead.AddDynamic(this, &UCombatManagerComponent::OnDeadAICharacter);

			auto* AICharacter{CombatController->GetCharacter()};
			AICharacters.AddUnique(AICharacter);
		}
	}
}

bool UCombatManagerComponent::OnCheckAttackPrepared()
{
	return true;
}

void UCombatManagerComponent::OnDeadAICharacter(AActor* CharacterActor)
{
}
