// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerHUDWidget.h"

#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetNormalizedHealth() const
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn == nullptr) { return 0.f; }
	
	const auto Component = PlayerPawn->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if (HealthComponent == nullptr) { return 0.f; }
	
	return HealthComponent->GetNormalizedHealth();
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn == nullptr) { return false; }
	
	const auto Component = PlayerPawn->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if (WeaponComponent == nullptr) { return false; }
	
	return WeaponComponent->TryGetAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::TryGetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn == nullptr) { return false; }
	
	const auto Component = PlayerPawn->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if (WeaponComponent == nullptr) { return false; }
	
	return WeaponComponent->TryGetWeaponUIData(UIData);
}
