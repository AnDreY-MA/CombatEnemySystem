// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_Perception.h"
#include "Controllers/CombatEnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/CombatEnemyStateComponent.h"
#include "LogCombatEnemySystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_Perception)

EStateTreeRunStatus USTT_Perception::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

    PerceptionComponent = ControllerContext->GetAIPerceptionComponent();
    check(PerceptionComponent.IsValid());

    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &USTT_Perception::OnPerceptionUpdated);
    ControllerContext->OnEnemyTargetUpdated.AddUObject(this, &USTT_Perception::OnTargetUpdated);

    return EStateTreeRunStatus::Running;
}

void USTT_Perception::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
    Clear();

    Super::ExitState(Context, Transition);
}

void USTT_Perception::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor) return;

    if (ETeamAttitude::Hostile != ControllerContext->GetTeamAttitudeTowards(*Actor->GetInstigator()->GetController())) return;

    UE_LOG(LogCombatEnemySystem, Display, TEXT("Update Actor - %s"), *Actor->GetName());

    CheckSight(Actor, Stimulus);
    CheckHearing(Actor, Stimulus);

}

const TPair<bool, bool> USTT_Perception::CanSense(const FAIStimulus& InStimulus, const TSubclassOf<UAISense>& InCheckSenseClass) const
{
    const TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(ControllerContext->GetWorld(), InStimulus);
    const bool bCurrentSense{ SenseClass == InCheckSenseClass };
    return { bCurrentSense && InStimulus.WasSuccessfullySensed(), bCurrentSense };
}

void USTT_Perception::CheckSight(AActor* InActor, const FAIStimulus& InStimulus)
{
    const auto [bSuccess, bCurrentSense] = CanSense(InStimulus, SightSenseClass);
    if (bCurrentSense == false) return;

    if (const double Distance = FVector::Dist(InActor->GetActorLocation(), ControllerContext->GetPawn()->GetActorLocation());
        Distance <= MinDistanceForTimer)
    {
        SetAggresive(InActor);
        return;
    }

    if (bSuccess)
    {
        UE_LOG(LogCombatEnemySystem, Display, TEXT("OnSight"));
        SendEvent(SightDetectEvent);
        StartAggressive(InActor);
    }
    
    else if (!bSuccess)
    {
        HandleLostTarget(InActor);
    }
    
}

void USTT_Perception::HandleLostTarget(const AActor* InActor)
{
    SendEvent(InstigateEvent);

    GetWorld()->GetTimerManager().ClearTimer(TimerDetection);
   
    InstigateLocation = InActor->GetActorLocation();
    TargetActor = nullptr;
    
    TypeInstigate = NormalInstigate;

    UE_LOG(LogCombatEnemySystem, Display, TEXT("HandleLostTarget"));

}

void USTT_Perception::StartAggressive(AActor* InActor)
{
    if (bAggressive) return;

    const FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &USTT_Perception::SetAggresive, InActor);
    GetWorld()->GetTimerManager().SetTimer(TimerDetection, Delegate, TimeAggresive, false);

    UE_LOG(LogCombatEnemySystem, Display, TEXT("Aggressive behavior initiated."));

}

void USTT_Perception::CheckHearing(const AActor* InActor, const FAIStimulus& InStimulus)
{
    const auto [bSuccess, bCurrentSense] = CanSense(InStimulus, HearSenseClass);
    if (bCurrentSense == false) return;

    if (bSuccess && !bAggressive && CurrentSense != SightDetectEvent)
    {
        UE_LOG(LogCombatEnemySystem, Display, TEXT("Hearing"));

        const float InNoise{ InStimulus.Strength };

        TypeInstigate = HearStrenghtNormal <= InNoise ? NormalInstigate : HighInstigate;

        InstigateLocation = InActor->GetActorLocation();
        
        SendEvent(HearDetectEvent);
    }

}

void USTT_Perception::Clear()
{
    if (ControllerContext)
    {
        ControllerContext->OnEnemyTargetUpdated.RemoveAll(this);
    }

    if (PerceptionComponent.IsValid())
    {
        PerceptionComponent->OnTargetPerceptionUpdated.RemoveAll(this);
        PerceptionComponent->SetActive(false);
    }

    GetWorld()->GetTimerManager().ClearTimer(TimerDetection);

}

void USTT_Perception::SetAggresive(AActor* InActor)
{
    if (!InActor)
    {
        UE_LOG(LogCombatEnemySystem, Warning, TEXT("Invalid actor in SetAggressive"));
        FinishTask(false);
        return;
    }

    Clear();

    UE_LOG(LogCombatEnemySystem, Display, TEXT("Set Aggressive"));
    SendEvent(Aggressive);

    TargetActor = InActor;
    ControllerContext->UpdateTargetActor(InActor);
    bAggressive = true;
    

}

void USTT_Perception::SendEvent(const FGameplayTag& InEvent)
{
    if (bAggressive) return;

    UE_LOG(LogCombatEnemySystem, Display, TEXT("Perception event: %s"), *InEvent.ToString());
    CurrentSense = InEvent;
    ControllerContext->GetCombatStateComponent_Implementation()->SendStateTreeEvent(InEvent);

}

void USTT_Perception::OnTargetUpdated(AActor* InTargetActor)
{
    if (InTargetActor)
    {
        SetAggresive(InTargetActor);
    }
    
}