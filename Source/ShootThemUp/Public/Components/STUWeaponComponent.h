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
	void Reload();
	bool TryGetWeaponUIData(FWeaponUIData& UIData) const;
	bool TryGetAmmoData(FAmmoData& AmmoData) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<FWeaponData> WeaponsData;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;
	
	UPROPERTY()
	UAnimMontage* CurrentWeaponReloadAnimMontage = nullptr;

	int CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	static void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Parent, const FName& SocketName);
	void SpawnWeapons();
	void EquipWeapon(int WeaponIndex);
	void PlayAnimMontage(UAnimMontage* Animation) const;
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);
	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;
	void OnClipEmpty();
	void ChangeClip();
};
