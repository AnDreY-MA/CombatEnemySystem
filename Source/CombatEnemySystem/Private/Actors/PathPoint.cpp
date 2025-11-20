// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PathPoint.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PathPoint)

APathPoint::APathPoint(const FObjectInitializer& InObjectInitializer) :
	Super(InObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

}

APathPoint* APathPoint::GetNextPathPoint_Implementation() const
{
	return NextPoint.Get();
}
