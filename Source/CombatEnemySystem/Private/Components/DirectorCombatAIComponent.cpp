// Copyright Red&White lynx. All Rights Reserved.


#include "Components/DirectorCombatAIComponent.h"

#include "AIController.h"
#include "LogCombatEnemySystem.h"
#include "Characters/CombatEnemyCharacter.h"
#include "Components/CombatCoverComponent.h"
#include "Components/StateTreeComponent.h"
#include "Controllers/CombatEnemyController.h"
#include "Controllers/EnemyControlInterface.h"
#include "Data/EnemyData.h"
#include "Data/EnemyDataInterface.h"
#include "Interfaces/CombatEnemyInterface.h"
#include "Kismet/KismetArrayLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DirectorCombatAIComponent)

UDirectorCombatAIComponent::UDirectorCombatAIComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

void UDirectorCombatAIComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAttackerLevels = DefaultAttackerLevels;
	
}

bool UDirectorCombatAIComponent::ReserveLevelAttack(const AAIController* InController, const FGameplayTag& InLevel)
{
	if (!CanReserveAttack(InController, InLevel)) return false;
    
	int32& CurrentPoint = CurrentAttackerLevels[InLevel];
	--CurrentPoint;
	
	ReserveHolders.Add(InController);

	return true;
	
}

void UDirectorCombatAIComponent::ReleaseLevelAttack(const AAIController* InController, const FGameplayTag& InLevel)
{
	if (!ReserveHolders.Remove(InController)) return;
	
	if (!CurrentAttackerLevels.Contains(InLevel) || !DefaultAttackerLevels.Contains(InLevel)) 
	{
		UE_LOG(LogCombatEnemySystem, Error, TEXT("Key %s not found!"), *InLevel.ToString());
		return;
	}

	int32& CurrentPoint = CurrentAttackerLevels[InLevel];
	CurrentPoint = FMath::Clamp(CurrentPoint + 1, 0, DefaultAttackerLevels[InLevel]);

}

bool UDirectorCombatAIComponent::CanReserveAttack(const AAIController* InController, const FGameplayTag& InLevel) const
{
	if (!IsValid(InController))
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("ReserveLevelAttack: invalid controller"));
		return false;
	}

	if (ReserveHolders.Contains(InController))
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("Controller %s already holds reservation"), *InController->GetName());
		return false;
	}

	if (const int32* Points = CurrentAttackerLevels.Find(InLevel))
	{
		if (*Points > 0)
			return true;
	}
	
	return false;
}

void UDirectorCombatAIComponent::OnEnemyDead(const ACombatEnemyCharacter* EnemyCharacter, const ACombatEnemyController* EnemyController)
{
	if (EnemyController)
	{
		EnemyControllers.Remove(EnemyController);

		const FEnemyData& Data = IEnemyDataInterface::Execute_GetData(EnemyController);
		ReleaseLevelAttack(EnemyController, Data.AttackLevel);
	}
	else
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("DirectorAI: EnemyDestroyed "))
	}
}

void UDirectorCombatAIComponent::RegisterActiveCombatEnemy(AAIController* InController)
{
	if (!IsValid(InController) || EnemyControllers.Contains(InController)) return;
	
	EnemyControllers.Add(InController);
	
	if (const auto Pawn {InController->GetPawn<ACombatEnemyCharacter>()}; Pawn)
	{
		Pawn->OnDead.AddDynamic(this, &UDirectorCombatAIComponent::OnEnemyDead);
	}
	
	if (!TargetActor.IsValid())
	{
		TargetActor = IEnemyControlInterface::Execute_GetTargetActor(InController);
		if (!TargetActor.IsValid()) return;
		
		if (auto* CoverComponent{TargetActor->FindComponentByClass<UCombatCoverComponent>()}; CoverComponent)
		{
			CoverComponent->OnCoverChanged.AddDynamic(this, &UDirectorCombatAIComponent::StartTargetCoverTaked);
		}
	}

}

void UDirectorCombatAIComponent::StartTargetCoverTaked(const bool bIsCover, const EHeightType HeightType)
{
	if (!TargetActor.IsValid() || !bIsCover) return;
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDirectorCombatAIComponent::TriggerThrowGrenade, TimeForGrenade);

	UE_LOG(LogCombatEnemySystem, Display, TEXT("Start timer for Throw Grenade"));

}

void UDirectorCombatAIComponent::TriggerThrowGrenade()
{
	if (EnemyControllers.Num() == 0 || bCanThrow == false) return;
	
	if (TryRequestThrowGrenade())
	{
		bCanThrow = false;
		FTimerHandle TimerGrenadeHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerGrenadeHandle, this, &UDirectorCombatAIComponent::ApplyCoolDownGrenade, GrenadeCooldown);
	}
	
}

void UDirectorCombatAIComponent::ApplyCoolDownGrenade()
{
	bCanThrow = true;
	
}

bool UDirectorCombatAIComponent::TryRequestThrowGrenade() const
{
	auto RequestThrow = [this]()
	{
		const int32 RandomIndex {FMath::RandRange(0, EnemyControllers.Num() - 1)};
		const auto* Controller = EnemyControllers[RandomIndex];
		return Controller && ICombatEnemyInterface::Execute_CanThrowGrenade(Controller) ? Controller : nullptr;
	};

	const auto* CurrentController {RequestThrow()};
	if (!CurrentController) return false;

	auto* StateTreeComponent {CurrentController->FindComponentByClass<UStateTreeComponent>()};
	StateTreeComponent->SendStateTreeEvent(GrenadeEvent);
	return true;
	
}

