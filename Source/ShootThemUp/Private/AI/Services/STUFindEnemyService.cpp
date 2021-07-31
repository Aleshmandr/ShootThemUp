// Shoot Them Up Game. All Rights Reserved.


#include "AI/Services/STUFindEnemyService.h"

#include "AIController.h"
#include "STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFindEnemyService::USTUFindEnemyService()
{
	NodeName = "Find Enemy";
	
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller->FindComponentByClass<USTUAIPerceptionComponent>();

		if(PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
}
