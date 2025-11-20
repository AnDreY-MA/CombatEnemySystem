// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CombatAIDebugComponent.h"

#include "LogCombatEnemySystem.h"
#include "Components/StateTreeAIComponent.h"
#include "Widgets/CombatAIDebugWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CombatAIDebugComponent)

UCombatAIDebugComponent::UCombatAIDebugComponent(const FObjectInitializer& InObjectInitializer) :
	Super(InObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickInterval = 1.5f;
	bTickInEditor = false;

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetGenerateOverlapEvents(false);
	BlendMode = EWidgetBlendMode::Transparent;

}

void UCombatAIDebugComponent::BeginPlay()
{
	Super::BeginPlay();

	SetVisibility(false);

	StateTreeComponent = GetOwner()->GetInstigatorController()->FindComponentByClass<UStateTreeAIComponent>();
	check(StateTreeComponent.IsValid());

	if (!InitializeDebugWidget()) return;

	EnableDebug(bDebug, bDebug);
	
}

void UCombatAIDebugComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TRACE_CPUPROFILER_EVENT_SCOPE(UCombatAIDebugComponent::TickComponent);

	if (!bDebug && !StateTreeComponent.IsValid() && !DebugWidget) return;

	SetTasks();

}

bool UCombatAIDebugComponent::InitializeDebugWidget()
{
	DebugWidget = Cast<UCombatAIDebugWidget>(GetUserWidgetObject());

	if (!DebugWidget)
	{
		UE_LOG(LogCombatEnemySystem, Warning, TEXT("%s: No widget debug on %s"), *GetName(), *GetOwner()->GetName());
		return false;
	}
	
	return true;
}

void UCombatAIDebugComponent::EnableDebug(const bool InbEnabled, const bool InbIsVisible)
{
	if (!StateTreeComponent.IsValid()) return;

	PrimaryComponentTick.SetTickFunctionEnable(InbEnabled);

	SetVisibility(InbEnabled ? InbIsVisible : false);

	if (InbEnabled)
	{
		SetAgentDescription();
	}
}

void UCombatAIDebugComponent::StopDebug()
{
	EnableDebug(false, false);

	StateTreeComponent.Reset();
	
}

void UCombatAIDebugComponent::SetAgentDescription() const
{
	if (!DebugWidget) return;

	const FString CharacterText = FString::Printf(TEXT("ID: %s"), *GetOwner()->GetName());
	const FString ControllerText = FString::Printf(TEXT("Controller: %s"), *GetOwner()->GetInstigatorController()->GetName());

	DebugWidget->SetTextCharacter(FText::FromString(CharacterText.Left(30)));
	DebugWidget->SetTextController(FText::FromString(ControllerText.Left(30)));
}

void UCombatAIDebugComponent::SetTasks() const
{
	const TArray<FName>& StateNames = StateTreeComponent->GetActiveStateNames();
	FString Tasks = FString::Printf(TEXT("Task: "));
	for (const FName& Name : StateNames)
	{
		Tasks += Name.ToString() + " ";
	}
	DebugWidget->SetTasks(FText::FromString(Tasks));
}

void UCombatAIDebugComponent::SetScores() const
{
}
