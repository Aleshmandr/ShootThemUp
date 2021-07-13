// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
