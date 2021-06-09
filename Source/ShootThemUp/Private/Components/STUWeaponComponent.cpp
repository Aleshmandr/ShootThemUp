// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUWeaponComponent.h"

#include "STUEquipFinishedAnimNotify.h"
#include "STUReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

class ASTUBaseWeapon;

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::StartFire()
{
	if (CanFire())
	{
		CurrentWeapon->StartFire();
	}
}

void USTUWeaponComponent::StopFire()
{
	if (CurrentWeapon == nullptr) return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character || !GetWorld()) { return; }

	for (auto WeaponData : WeaponsData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponData.WeaponClass);
		if (Weapon == nullptr) { continue; }
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnClipEmpty);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USTUWeaponComponent::EquipWeapon(int WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= WeaponsData.Num()) { return; }

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) { return; }
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	CurrentWeapon = Weapons[WeaponIndex];
	const auto CurrentWeaponData = WeaponsData.FindByPredicate([&](const FWeaponData& Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentWeaponReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	PlayAnimMontage(EquipAnimMontage);
	EquipAnimInProgress = true;
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) { return; }
	Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
	auto EquipFinishNotify = FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishNotify)
	{
		EquipFinishNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}


	for (auto WeaponData : WeaponsData)
	{
		auto ReloadFinishNotify = FindNotifyByClass<USTUReloadFinishedAnimNotify>(WeaponData.ReloadAnimMontage);
		if (ReloadFinishNotify)
		{
			ReloadFinishNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
		}
	}
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComp) { return; }
	EquipAnimInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComp) { return; }
	ReloadAnimInProgress = false;
}

bool USTUWeaponComponent::CanFire() const
{
	return CurrentWeapon != nullptr && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
	return CurrentWeapon != nullptr && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void USTUWeaponComponent::OnClipEmpty()
{
	ChangeClip();
}

void USTUWeaponComponent::ChangeClip()
{
	if (!CanReload()) { return; }
	
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentWeaponReloadAnimMontage);
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Parent, const FName& SocketName)
{
	if (!Weapon || !Parent) { return; }
	
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Parent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::NextWeapon()
{
	if (CanEquip())
	{
		CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		EquipWeapon(CurrentWeaponIndex);
	}
}

void USTUWeaponComponent::Reload()
{
	ChangeClip();
}
