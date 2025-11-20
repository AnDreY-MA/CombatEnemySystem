// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/RunEQSQuery_Task.h"

#include "AIController.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RunEQSQuery_Task)

URunEQSQuery_Task::URunEQSQuery_Task(const FObjectInitializer& InInitializer) :
	Super(InInitializer), QueryConfig(), RunMode(EEnvQueryRunMode::SingleResult)
{
}

URunEQSQuery_Task* URunEQSQuery_Task::RunEQSQuery_Task(
	UObject* WorldContext, AAIController* InAIController, UEnvQuery* InEnvironmentQuery, const TArray<FAIDynamicParam>& InQueryConfig, TEnumAsByte<EEnvQueryRunMode::Type> InRunMode)
{
	if(!InAIController)
	{
		return nullptr;
	}
	
	URunEQSQuery_Task* FindTask{NewObject<URunEQSQuery_Task>(InAIController)};
	FindTask->Controller = InAIController;
	FindTask->EnvQuery = InEnvironmentQuery;
	FindTask->QueryConfig = InQueryConfig;
	FindTask->RunMode = InRunMode;
	
	//FindTask->RegisterWithGameInstance(WorldContext);
	
	return FindTask;
}

void URunEQSQuery_Task::Activate()
{
	FEnvQueryRequest QueryRequest(EnvQuery.Get(), Controller->GetPawn());

	for (FAIDynamicParam& Param : QueryConfig)
	{
		QueryRequest.SetDynamicParam(Param);
	}

	RequestId = QueryRequest.Execute(RunMode, this, &URunEQSQuery_Task::OnQueryFinished);

}

void URunEQSQuery_Task::OnQueryFinished(TSharedPtr<FEnvQueryResult> InResult)
{
	if (InResult->IsSuccessful() && InResult->Items.Num() > 0)
	{
		OnSuccess.Broadcast(InResult->GetItemAsLocation(0), InResult->GetItemAsActor(0));
	}
	else
	{
		OnFailed.Broadcast(FVector::ZeroVector, nullptr);
	}

	if (UEnvQueryManager* QueryManager = UEnvQueryManager::GetCurrent(Controller->GetWorld()); QueryManager)
	{
		QueryManager->AbortQuery(RequestId);
	}
	
	SetReadyToDestroy();


}