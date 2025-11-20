#include "StateTree/Evaluators/STE_StatsTracker.h"
#include "StateTreeExecutionContext.h"
#include "Characters/CombatEnemyCharacter.h"
#include "Data/EnemyData.h"
#include "Data/EnemyDataInterface.h"
#include "StateTreeAsyncExecutionContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STE_StatsTracker)

void FSTE_StatsTracker::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);

	auto& InstanceData = Context.GetInstanceData(*this);
	const FEnemyData& Data = IEnemyDataInterface::Execute_GetData(InstanceData.ContextPawn);
	
	InstanceData.AttackLevel = Data.AttackLevel;
	InstanceData.MaxHealth = Data.Health;
	InstanceData.AttackSpeed = Data.AttackSpeed;
	InstanceData.TimeAggression = Data.TimeForAggresionSight;
	InstanceData.NormalNoise = Data.NormalNoise;
	InstanceData.HighNoise = Data.HighNoise;
	
	InstanceData.ContextPawn->OnHealthChanged.BindLambda(
		[WeakContext = Context.MakeWeakExecutionContext()](const float HealthPercent)
		{
			FInstanceDataType* LambdaInstanceData = WeakContext.MakeStrongExecutionContext().GetInstanceDataPtr<FInstanceDataType>();
	
			if (!LambdaInstanceData) return;

			LambdaInstanceData->CurrentPercentHealth = HealthPercent;
			
		}
		);

}