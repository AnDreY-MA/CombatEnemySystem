// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/RunEQSQuery_Task.h"

#include "AIController.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RunEQSQuery_Task)

URunEQSQuery_Task::URunEQSQuery_Task(const FObjectInitializer& InInitializer) :
	Super(InInitializer), RunMode(EEnvQueryRunMode::SingleResult)
{
}

URunEQSQuery_Task* URunEQSQuery_Task::FindAroundTargetLocation_Task(
	AAIController* InAIController, UEnvQuery* InEnvironmentQuery, TEnumAsByte<EEnvQueryRunMode::Type> InRunMode)
{
	if(!InAIController)
	{
		return nullptr;
	}
	
	URunEQSQuery_Task* FindTask{NewObject<URunEQSQuery_Task>()};
	FindTask->Controller = InAIController;
	FindTask->EnvQuery = InEnvironmentQuery;
	FindTask->RunMode = InRunMode;
	
	return FindTask;
}

void URunEQSQuery_Task::Activate()
{
	FEnvQueryRequest QueryRequest(EnvQuery.Get(), Controller->GetPawn());
	QueryRequest.Execute(RunMode, this, &URunEQSQuery_Task::OnQueryFinished);

}

void URunEQSQuery_Task::OnQueryFinished(TSharedPtr<FEnvQueryResult> EnvQueryResult)
{
	if (EnvQueryResult->IsSuccsessful() && EnvQueryResult->Items.Num() > 0)
	{
		OnSuccess.Broadcast(EnvQueryResult->GetItemAsLocation(0), EnvQueryResult->GetItemAsActor(0));
	}
	else
	{
		OnFailed.Broadcast(FVector::ZeroVector, nullptr);
	}

}