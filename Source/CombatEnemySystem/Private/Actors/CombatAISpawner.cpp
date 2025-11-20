// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CombatAISpawner.h"
#include "Characters/CombatEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Controllers/CombatEnemyController.h"

//ACombatAISpawner::ACombatAISpawner(const FObjectInitializer& InInitializer) :
//	Super(InInitializer), bSpawnOnBegin(true), SpawnCount(1)
//{
//	PrimaryActorTick.bCanEverTick = false;
//
//}
//
//void ACombatAISpawner::BeginPlay()
//{
//	Super::BeginPlay();
//
//	if (bSpawnOnBegin)
//	{
//		Spawn();
//	}
//	
//}
//
//void ACombatAISpawner::Spawn()
//{
//	if (!SpawnCharacterClass || SpawnCount == 0) return;
//
//	if (UAssetManager* Manager{ UAssetManager::GetIfValid() }; Manager)
//	{
//		auto& Streamable = Manager->GetStreamableManager();
//		Streamable.RequestAsyncLoad(SpawnCharacterClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this]()
//			{
//				UClass* LoadedClass = SpawnCharacterClass.LoadSynchronous();
//				UWorld* World{ this->GetWorld() };
//				FTransform SpawnTransform;
//				SpawnTransform.SetLocation(this->GetActorLocation());
//				SpawnTransform.SetRotation(this->GetActorRotation().Quaternion());
//				for (size_t i = 0; i < SpawnCount; ++i)
//				{
//					auto* CharacterSpawned = World->SpawnActorDeferred<ACombatEnemyCharacter>(LoadedClass, SpawnTransform);
//					CharacterSpawned->FinishSpawning(SpawnTransform);
//				}	
//
//			}));
//	}
//}