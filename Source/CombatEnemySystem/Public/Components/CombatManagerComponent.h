// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatManagerComponent.generated.h"


class ACombatEnemyController;

UCLASS(ClassGroup=(CombatEnemy), meta=(BlueprintSpawnableComponent))
class COMBATENEMYSYSTEM_API UCombatManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	explicit UCombatManagerComponent(const FObjectInitializer& InInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	bool OnCheckAttackPrepared();

	UFUNCTION()
	void OnDeadAICharacter(AActor* CharacterActor);

private:
	UPROPERTY(EditDefaultsOnly, Category="Combat AI")
	TSubclassOf<ACombatEnemyController> CombatAIControllerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<ACharacter*> AICharacters;
	
	UPROPERTY()
	bool bAttacking;

};