// Shoot Them Up Game. All Rights Reserved.


#include "AI/Services/STUFireService.h"

#include "AIController.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFireService::USTUFireService()
{
	NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Controller = OwnerComp.GetAIOwner();
	const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();
	if (WeaponComponent)
	{
		CheckAttackTarget(OwnerComp)? WeaponComponent->StartFire() : WeaponComponent->StopFire();
	}
}

bool USTUFireService::CheckAttackTarget(UBehaviorTreeComponent& OwnerComp) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard == nullptr) return false;

	const auto Enemy = Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	return Enemy != nullptr;
}
