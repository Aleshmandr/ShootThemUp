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
		const auto STUGameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (STUGameMode)
		{
			STUGameMode->OnRoundStarted.AddUObject(this, &USTUPlayerHUDWidget::HandleRoundStart);
		}
	}
	return Super::Initialize();
}

void USTUPlayerHUDWidget::HandleRoundStart(int Round)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
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
