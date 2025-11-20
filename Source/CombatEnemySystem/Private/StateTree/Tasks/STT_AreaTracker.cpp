// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTree/Tasks/STT_AreaTracker.h"
#include "GameFramework/Pawn.h"
#include "Controllers/CombatEnemyController.h"
#include <CollisionDebugDrawingPublic.h>
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CombatEnemyStateComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STT_AreaTracker)

DEFINE_LOG_CATEGORY_STATIC(LogAreaTracker, All, All)


EStateTreeRunStatus USTT_AreaTracker::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);
	
	PawnContext = ControllerContext->GetPawn();
	OwnerWorld = PawnContext->GetWorld();

	TraceDelegate.BindUObject(this, &USTT_AreaTracker::OnTraceDelegate);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]()
	{
		DoTrace();
	});

	//OwnerWorld->GetTimerManager().SetTimer(TimerHandle, this, &USTT_AreaTracker::DoTrace, CheckTraceInterval, true);
	OwnerWorld->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, CheckTraceInterval, true);

	return EStateTreeRunStatus::Running;
}

void USTT_AreaTracker::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	OwnerWorld->GetTimerManager().ClearTimer(TimerHandle);
	PawnContext.Reset();
	OwnerWorld.Reset();

}

void USTT_AreaTracker::DoTrace()
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	if (!PawnContext.IsValid()) return;

	const FVector TraceLocation{ PawnContext->GetActorLocation() };

	const FCollisionShape Shape{ FCollisionShape::MakeSphere(SphereRadius) };

	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.bTraceComplex = false;
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
	QueryParams.bDebugQuery = bDebug;
#endif
	FCollisionResponseParams ResponseParams = FCollisionResponseParams::DefaultResponseParam;
	//ResponseParams.CollisionResponse.SetResponse(TraceChannel, ECollisionResponse::ECR_Block);

	OwnerWorld->AsyncSweepByChannel(EAsyncTraceType::Single, TraceLocation, TraceLocation, PawnContext->GetActorQuat(),
		TraceChannel, Shape, QueryParams, ResponseParams, &TraceDelegate);
#if !UE_BUILD_SHIPPING
	if (bDebug)
	{
		DrawSphereSweeps(GetWorld(), TraceLocation, TraceLocation, Shape.GetSphereRadius(), {}, LifeTimeDebug);
	}
#endif

}

void USTT_AreaTracker::OnTraceDelegate(const FTraceHandle& InTraceHandle, FTraceDatum& InTraceDatum)
{
	if (!InTraceDatum.OutHits.Num()) return;

	if (!InTraceDatum.OutHits.IsValidIndex(0)) return;
	
	auto* HitActor = InTraceDatum.OutHits[0].GetActor();
	if (!HitActor) return;

	if (HitActor->GetOwner()->IsA(PawnContext->GetClass())) return;

	if (!ActorTracked)
	{
		ActorTracked = HitActor;
		ActorTracked->OnDestroyed.AddDynamic(this, &USTT_AreaTracker::OnTrackedActorDestroyed);
#if !UE_BUILD_SHIPPING
		if (bDebug)
		{
			UKismetSystemLibrary::PrintString(PawnContext.Get(), "ActorTracked " + ActorTracked->GetName());
		}
#endif

		UE_LOG(LogAreaTracker, Display, TEXT("ActorTracked is %s"), *ActorTracked->GetName());

		auto* StateComponent = ControllerContext->GetCombatStateComponent_Implementation();
		StateComponent->SendStateTreeEvent(EventTracked);
	}
}

void USTT_AreaTracker::OnTrackedActorDestroyed(AActor* DestroyedActor)
{
	if (ActorTracked && ActorTracked == DestroyedActor)
	{
		ActorTracked = nullptr;
	}
}
