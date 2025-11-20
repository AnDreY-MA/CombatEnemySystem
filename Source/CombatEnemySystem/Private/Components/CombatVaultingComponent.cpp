// Copyright Red&White lynx. All Rights Reserved.


#include "Components/CombatVaultingComponent.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UCombatVaultingComponent::UCombatVaultingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.2f;

}


void UCombatVaultingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = GetOwner<ACharacter>();
	MotionWarpingComponent = OwnerCharacter->FindComponentByClass<UMotionWarpingComponent>();
}

void UCombatVaultingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bAutoDetect) return;

	DetectWall();
	
}

void UCombatVaultingComponent::DetectWall()
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCTION__);

	if (const double VelocityLength = OwnerCharacter->GetVelocity().Length(); VelocityLength > 0)
	{
		const FVector Start = OwnerCharacter->GetActorLocation();
		const FVector End = Start + UKismetMathLibrary::GetForwardVector(OwnerCharacter->GetActorRotation()) * (VelocityLength / 10);
		FHitResult HitResult;
		const TArray<TObjectPtr<AActor>> IgnoreActors = {OwnerCharacter};
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, Radius, TraceTypeQuery, false, IgnoreActors,DrawDebugType, HitResult, true);
	}
}