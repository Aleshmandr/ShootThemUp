// Shoot Them Up Game. All Rights Reserved.


#include "AI/Tasks/STUFindRandomLocationTaskNode.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFindRandomLocationTaskNode::USTUFindRandomLocationTaskNode()
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type USTUFindRandomLocationTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) { return EBTNodeResult::Failed; }

	const auto Pawn = Controller->GetPawn();

	if(!Pawn) { return EBTNodeResult::Failed; }
	FNavLocation ResultLocation;
	const auto NavigationSystem = UNavigationSystemV1::GetCurrent(Controller);
	
	if(NavigationSystem && NavigationSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, ResultLocation))
	{
		Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, ResultLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
