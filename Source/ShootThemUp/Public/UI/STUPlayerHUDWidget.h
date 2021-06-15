// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUWeaponComponent;
class USTUHealthComponent;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetNormalizedHealth() const;
	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetAmmoData(FAmmoData& AmmoData) const;
	UFUNCTION(BlueprintCallable, Category="UI")
	bool TryGetWeaponUIData(FWeaponUIData& UIData) const;
	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;
	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerSpectating() const;
	
private:
	USTUWeaponComponent* GetWeaponComponent() const;
	USTUHealthComponent* GetHealthComponent() const;
};
