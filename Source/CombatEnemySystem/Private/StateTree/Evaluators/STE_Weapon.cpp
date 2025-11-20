#include "StateTree/Evaluators/STE_Weapon.h"

#include "StateTreeExecutionContext.h"
#include "Characters/CombatEnemyCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(STE_Weapon)

void FSTE_Weapon::TreeStart(FStateTreeExecutionContext& Context) const
{
	const auto& InstanceData = Context.GetInstanceData(*this);
	InstanceData.CharacterContext->OnWeaponAmmoChanged.BindLambda([WeakContext = Context.MakeWeakExecutionContext()](const int32 InAmmoAmount)
	{
		const auto StrongContext = WeakContext.MakeStrongExecutionContext();
		if (auto* InstanceDataType = StrongContext.GetInstanceDataPtr<FInstanceDataType>(); InstanceDataType)
		{
			InstanceDataType->AmmoAmount = InAmmoAmount;
			if (InstanceDataType->AmmoAmount <= 0)
			{
				StrongContext.SendEvent(InstanceDataType->EventAmmoEmpty);
			}
		}
	});
	
	FStateTreeEvaluatorCommonBase::TreeStart(Context);

}