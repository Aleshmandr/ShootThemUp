// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

class ASTUBaseWeapon;

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::StartFire()
{
	if (CurrentWeapon == nullptr) return;
	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if (CurrentWeapon == nullptr) return;
	CurrentWeapon->StopFire();
}

// Called when the game starts or when spawned
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr) return;

	CurrentWeapon = World->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (CurrentWeapon == nullptr) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}
