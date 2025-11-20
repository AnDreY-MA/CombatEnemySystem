// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PatrolerComponent.h"

UPatrolerComponent::UPatrolerComponent(const FObjectInitializer& InInitializer) :
	Super(InInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

}