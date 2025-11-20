// Copyright Red&White lynx. All Rights Reserved.


#include "EnvQueries/Contexts/GetActorTartget_QueryContext.h"

#include "Controllers/EnemyControlInterface.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(GetActorTartget_QueryContext)

void UEQC_ActorTarget::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                  FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	if (const auto* Character {Cast<AActor>(QueryInstance.Owner.Get())}; Character)
	{
		if (const auto* Controller {Character->GetInstigatorController()}; Controller && Controller->Implements<UEnemyControlInterface>())
		{
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, IEnemyControlInterface::Execute_GetTargetActor(Controller));
			return;
		}
	}

	if (const auto* PlayerCharacter = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); PlayerCharacter)
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerCharacter);
	}
	
}
