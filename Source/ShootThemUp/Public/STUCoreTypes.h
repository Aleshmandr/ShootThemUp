﻿#pragma once
#include "STUCoreTypes.generated.h"

class UNiagaraSystem;
class ASTUBaseWeapon;


USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta = (EditConditions = "!IsInfinite"))
	int Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	bool IsInfinite;

	bool IsAmmoEmpty() const
	{
		return !IsInfinite && Clips <= 0 && IsClipEmpty();
	}

	bool IsClipEmpty() const
	{
		return Bullets <= 0;
	}
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* Crosshair;
};

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UMaterialInterface* Material;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FVector Size = FVector(5.0f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	float LifeTime = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	float FadeOutTime = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	float FadeScreenSize = 0.001f;
};

USTRUCT(BlueprintType)
struct FImpactFXData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* NiagaraSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FDecalData DecalData;
};

USTRUCT(BlueprintType)
struct FDeathData
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	const AController* KilledController;
	UPROPERTY()
	const AActor* KilledActor;
	UPROPERTY()
	const UDamageType* DamageType;
	UPROPERTY()
	const AController* InstigatedBy;
	UPROPERTY()
	const AActor* DamageCauser;
};

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "128"))
	int32 PlayersNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundsNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "600"))
	int32 RoundTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "30"))
	int32 RespawnTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "30"))
	int32 RoundEndRespawnThresh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "128"))
	int32 TeamsCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLinearColor> TeamColors;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, const FDeathData&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundStarted, int);
