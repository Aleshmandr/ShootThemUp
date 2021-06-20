// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/STUHealthPickup.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUHealthPickup::IsApplicableTo(APawn* Pawn) const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
	if (HealthComponent != nullptr)
	{
		return HealthComponent->TryHeal(HealAmount);
	}

	return false;
}
