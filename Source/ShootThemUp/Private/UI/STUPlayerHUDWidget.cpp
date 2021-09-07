// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerHUDWidget.h"

#include "STUGameModeBase.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"


bool USTUPlayerHUDWidget::Initialize()
{
	if (GetWorld())
	{
		const auto Player = GetOwningPlayer();
		if(Player)
		{
			Player->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::HandlePlayerPawnChange);
			HandlePlayerPawnChange(GetOwningPlayerPawn());
		}
	}
	return Super::Initialize();
}

void USTUPlayerHUDWidget::HandlePlayerPawnChange(APawn* NewPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::HandleHealthChange);
	}
}

void USTUPlayerHUDWidget::HandleHealthChange(float Health, float Delta)
{
	if (Delta < 0.0f)
	{
		OnDamage();
	}
}

float USTUPlayerHUDWidget::GetNormalizedHealth() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent == nullptr) { return 0.f; }

	return HealthComponent->GetNormalizedHealth();
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (WeaponComponent == nullptr) { return false; }

	return WeaponComponent->TryGetCurrentAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::TryGetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (WeaponComponent == nullptr) { return false; }

	return WeaponComponent->TryGetCurrentWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent != nullptr && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}
