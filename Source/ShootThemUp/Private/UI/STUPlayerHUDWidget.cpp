// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerHUDWidget.h"

#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetNormalizedHealth() const
{
	const auto HealthComponent = GetHealthComponent();
	if (HealthComponent == nullptr) { return 0.f; }

	return HealthComponent->GetNormalizedHealth();
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (WeaponComponent == nullptr) { return false; }

	return WeaponComponent->TryGetAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::TryGetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (WeaponComponent == nullptr) { return false; }

	return WeaponComponent->TryGetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	return HealthComponent != nullptr && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn == nullptr) { return nullptr; }

	const auto Component = PlayerPawn->GetComponentByClass(USTUWeaponComponent::StaticClass());
	return Cast<USTUWeaponComponent>(Component);
}

USTUHealthComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn == nullptr) { return nullptr; }

	const auto Component = PlayerPawn->GetComponentByClass(USTUHealthComponent::StaticClass());
	return Cast<USTUHealthComponent>(Component);
}
