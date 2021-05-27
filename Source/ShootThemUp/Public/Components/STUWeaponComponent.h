// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUBaseWeapon.h"
#include "STUWeaponComponent.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUWeaponComponent();
	void StartFire();
	void StopFire();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;
	
	void SpawnWeapon();
};
