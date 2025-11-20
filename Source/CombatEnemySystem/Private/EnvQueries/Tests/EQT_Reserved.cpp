// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvQueries/Tests/EQT_Reserved.h"

#include "Interfaces/DestinationActorInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EQT_Reserved)

UEQT_Reserved::UEQT_Reserved(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Medium;
	
	SetWorkOnFloatValues(false);
	
}

void UEQT_Reserved::RunTest(FEnvQueryInstance& QueryInstance) const
{
	Super::RunTest(QueryInstance);

	const UObject* QueryOwner = QueryInstance.Owner.Get();
	if (!QueryOwner) return;

	BoolValue.BindData(QueryOwner, QueryInstance.QueryID);
	
	const bool bWantAvailable = true;
		//BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		if (const auto* Actor = GetItemActor(QueryInstance, It.GetIndex());
			Actor && Actor->Implements<UDestinationActorInterface>())
		{
			const bool bResult {IDestinationActorInterface::Execute_IsAvailable(Actor)};
			It.SetScore(TestPurpose, FilterType, bResult, bWantAvailable);

		}
	}
	
}