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
	void NextWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	int CurrentWeaponIndex = 0;

	static void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Parent, const FName& SocketName);
	void SpawnWeapons();
	void EquipWeapon(int WeaponIndex);
};
