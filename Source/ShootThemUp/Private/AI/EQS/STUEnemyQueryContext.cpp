// Shoot Them Up Game. All Rights Reserved.


#include "AI/EQS/STUEnemyQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);

	if (Blackboard)
	{
		const auto Enemy = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKeyName));
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, Enemy);
	}
}
