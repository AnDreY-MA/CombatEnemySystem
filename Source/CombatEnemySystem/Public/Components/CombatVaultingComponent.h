// Copyright Red&White lynx. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CombatVaultingComponent.generated.h"

class UMotionWarpingComponent;

UCLASS( ClassGroup=(CombatAI), meta=(BlueprintSpawnableComponent) )
class COMBATENEMYSYSTEM_API UCombatVaultingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatVaultingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;

private:
	void DetectWall();

private:
	UPROPERTY(EditDefaultsOnly, Category = "CombatVaulting")
	bool bAutoDetect{false};
	UPROPERTY(EditDefaultsOnly, Category = "CombatVaulting")
	float Radius{25.f};
	UPROPERTY(EditDefaultsOnly, Category = "CombatVaulting")
	TEnumAsByte<ETraceTypeQuery> TraceTypeQuery{TraceTypeQuery1};
	UPROPERTY(EditDefaultsOnly, Category = "CombatVaulting")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType{EDrawDebugTrace::None};

	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	TWeakObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
		
};