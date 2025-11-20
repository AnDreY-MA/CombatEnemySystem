// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RunEQSQuery_Task.generated.h"

class UEnvQuery;
struct FEnvQueryResult;
class AAIController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFindingDelegate, const FVector&, Location, const AActor*, TargetItem);

UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncAction))
class COMBATENEMYSYSTEM_API URunEQSQuery_Task : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	explicit URunEQSQuery_Task(const FObjectInitializer& InInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, Category="AI|Tasks", meta=(WorldContext = "WorldContext", BlueprintInternalUseOnly = "true"))
	static URunEQSQuery_Task* RunEQSQuery_Task(UObject* WorldContext, AAIController* InAIController, UEnvQuery* InEnvironmentQuery, const TArray<FAIDynamicParam>& InQueryConfig, TEnumAsByte<EEnvQueryRunMode::Type> InRunMode = EEnvQueryRunMode::SingleResult);

	virtual void Activate() override;
		
	UPROPERTY(BlueprintAssignable)
	FOnFindingDelegate OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FOnFindingDelegate OnFailed;

	void OnQueryFinished(TSharedPtr<FEnvQueryResult> InResult);

private:
	TWeakObjectPtr<AAIController> Controller;
	TWeakObjectPtr<UEnvQuery> EnvQuery;

	UPROPERTY()
	TArray<FAIDynamicParam> QueryConfig;

	UPROPERTY()
	TEnumAsByte<EEnvQueryRunMode::Type> RunMode;

	int32 RequestId = INDEX_NONE;
	
};