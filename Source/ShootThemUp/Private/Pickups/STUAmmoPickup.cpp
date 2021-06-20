// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/STUAmmoPickup.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"

bool ASTUAmmoPickup::IsApplicableTo(APawn* Pawn) const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
	if (HealthComponent == nullptr || HealthComponent->IsDead()) { return false; }
	
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Pawn);
	if (WeaponComponent == nullptr) { return false; }

	return WeaponComponent->TryAddAmmo(WeaponType, Clips);
}
