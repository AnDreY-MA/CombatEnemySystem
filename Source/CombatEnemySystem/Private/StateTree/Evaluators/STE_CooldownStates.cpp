// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Evaluators/STE_CooldownStates.h"

#include "LogCombatEnemySystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STE_CooldownStates)

USTT_CooldownStates::USTT_CooldownStates(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bShouldCallTick = true;
	bHasLatentTick = true;
}

EStateTreeRunStatus USTT_CooldownStates::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	Super::EnterState(Context, Transition);
	
	CooldownTracker = this;

	//CooldownTimers = CooldownDefaults;
	//AvailableStates.Empty();
	for (auto& State : CooldownDefaults)
	{
		AvailableStates.Add(State.Key, true);
	}
	CooldownTimers.Empty();
	
	return EStateTreeRunStatus::Running;
}


EStateTreeRunStatus USTT_CooldownStates::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	Super::Tick(Context, DeltaTime);

	for (auto& State : CooldownTimers)
	{
		//UE_LOG(LogCombatEnemySystem, Display, TEXT("CooldownStates: Timer State - %s, %f"), *State.Key.ToString(), State.Value);

		bool& bIsAvailable = *AvailableStates.Find(State.Key);
		//UE_LOG(LogCombatEnemySystem, Display, TEXT("CooldownStates: Update State - %s, %d"), *State.Key.ToString(), bIsAvailable);
		if (!bIsAvailable)
		{
			State.Value -= DeltaTime;
		//	UE_LOG(LogCombatEnemySystem, Display, TEXT("CooldownStates: Update State - %s, %f"), *State.Key.ToString(), State.Value);
			if (State.Value <= 0.0f)
			{
				bIsAvailable = true;
				if (const float DefaultCooldown = *CooldownDefaults.Find(State.Key))
				{
					State.Value = DefaultCooldown;
				}
			}
		}
	}
	
	return EStateTreeRunStatus::Running;
}

void USTT_CooldownStates::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);

	CooldownTracker = nullptr;
}


void USTT_CooldownStates::UpdateCooldownState(const FName& InNameState, const bool InValue)
{
	if (!CooldownDefaults.Contains(InNameState))
	{
		//UE_LOG(LogCombatEnemySystem, Warning, TEXT("STE_CooldownStates: Unknown cooldown state: %s"), *InNameState.ToString());
		return;
	}
	
	bool& bAvailable  = AvailableStates.FindOrAdd(InNameState);
	bAvailable = InValue;

	AvailableStates[InNameState] = InValue;
	
	if (!InValue && !CooldownTimers.Contains(InNameState)) 
	{
		//UE_LOG(LogCombatEnemySystem, Display, TEXT("STE_CooldownStates: Apply Cooldown: %s"), *InNameState.ToString());
		CooldownTimers.Add(InNameState, *CooldownDefaults.Find(InNameState));
	}

}

const bool USTT_CooldownStates::IsAvailableState(const FName& InNameState) const
{
	if (!AvailableStates.Contains(InNameState)) return false;
	
	const bool bResult = *AvailableStates.Find(InNameState);
	
	//UE_LOG(LogCombatEnemySystem, Display, TEXT("Check Available: State %s - %d"), *InNameState.ToString(), bResult);
	
	return bResult;
}