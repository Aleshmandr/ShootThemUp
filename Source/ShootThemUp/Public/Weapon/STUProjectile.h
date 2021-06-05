// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

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
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	float Damage = 50.0f;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	float LifeTime = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	bool DoFullDamage;

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

private:
	FVector ShotDirection;
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Explode();
	AController* GetController() const;
	void IgnoreOwner(bool bShouldIgnore) const;
};
