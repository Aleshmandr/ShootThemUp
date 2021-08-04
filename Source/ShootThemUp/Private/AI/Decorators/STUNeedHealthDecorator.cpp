// Shoot Them Up Game. All Rights Reserved.


#include "AI/Decorators/STUNeedHealthDecorator.h"

#include "AIController.h"
#include "STUHealthComponent.h"

USTUNeedHealthDecorator::USTUNeedHealthDecorator()
{
	NodeName = "Need Health";
}

bool USTUNeedHealthDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto AIOwner = OwnerComp.GetAIOwner();
	if (AIOwner == nullptr) return false;

	const auto Pawn = AIOwner->GetPawn();
	if (Pawn == nullptr) return false;

	const auto HealthComponent = Pawn->FindComponentByClass<USTUHealthComponent>();
	if (HealthComponent == nullptr) return false;
	
	return HealthComponent->GetNormalizedHealth() <= NormalizedHealthThresh;
}
