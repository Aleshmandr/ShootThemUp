// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) const
{
	auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (Effects.Contains(PhysMat))
		{
			Effect = Effects[PhysMat];
		}
	}

	if (Effect.NiagaraSystem != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			Effect.NiagaraSystem,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation()
		);
	}


	auto Decal = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		Effect.DecalData.Material,
		Effect.DecalData.Size,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation()
	);

	if (Decal != nullptr)
	{
		Decal->SetFadeOut(Effect.DecalData.LifeTime, Effect.DecalData.FadeOutTime);
		Decal->SetFadeScreenSize(Effect.DecalData.FadeScreenSize);
	}
}
