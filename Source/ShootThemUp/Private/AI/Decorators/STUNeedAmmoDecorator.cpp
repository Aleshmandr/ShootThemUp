// Shoot Them Up Game. All Rights Reserved.


#include "AI/Decorators/STUNeedAmmoDecorator.h"

#include "AIController.h"
#include "STUWeaponComponent.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto AIOwner = OwnerComp.GetAIOwner();
	if (AIOwner == nullptr) return false;

	const auto Pawn = AIOwner->GetPawn();
	if (Pawn == nullptr) return false;

	const auto WeaponComponent = Pawn->FindComponentByClass<USTUWeaponComponent>();
	if (WeaponComponent == nullptr) return false;

	FAmmoData AmmoData;
	return WeaponComponent->TryGetAmmoData(WeaponType, AmmoData) && AmmoData.IsAmmoEmpty();
}
