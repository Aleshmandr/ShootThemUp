// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USTUWeaponFXComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASTUProjectile();
	void SetDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float Damage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float DestroyDelay = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	bool DoFullDamage;

	UPROPERTY(VisibleAnywhere, Category="VFX")
	USTUWeaponFXComponent* WeaponFXComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void OnExplode();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FVector ShotDirection;
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Explode();
	void TryDestroy();
	AController* GetController() const;
	void IgnoreOwner(bool bShouldIgnore) const;
	FTimerHandle LifeTimeTimerHandle;
	FTimerHandle DestroyDelayTimerHandle;
};
