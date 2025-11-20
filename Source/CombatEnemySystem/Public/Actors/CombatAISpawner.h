// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatAISpawner.generated.h"

class ACombatEnemyCharacter;
class ACombatEnemyController;

UCLASS(Category = "MamontAISystem")
class COMBATENEMYSYSTEM_API ACombatAISpawner : public AActor
{
	GENERATED_BODY()
	
//public:	
//	explicit ACombatAISpawner(const FObjectInitializer& InInitializer = FObjectInitializer::Get());
//
//	void Spawn();
//
//
//protected:
//	virtual void BeginPlay() override;
//
//private:
//	UPROPERTY(EditAnywhere, Category = "Spawner")
//	TSoftClassPtr<ACombatEnemyCharacter> SpawnCharacterClass;
//	UPROPERTY(EditAnywhere, Category = "Spawner")
//	TSubclassOf<ACombatEnemyController> SpawnController;
//
//	UPROPERTY(EditAnywhere, Category = "Spawner"/*, meta = (ClampMin = "0")*/)
//	uint32 SpawnCount;
//
//	UPROPERTY(EditAnywhere, Category = "Spawner")
//	bool bSpawnOnBegin;

};