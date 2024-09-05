// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PathPoint.h"

APathPoint::APathPoint(const FObjectInitializer& InObjectInitializer) :
	Super(InObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

}