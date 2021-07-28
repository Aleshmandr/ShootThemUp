// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STUProjectile.h"

#include "DrawDebugHelpers.h"
#include "STUWeaponFXComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogProjectile, All, All)

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(MovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	IgnoreOwner(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	GetWorldTimerManager().SetTimer(LifeTimeTimerHandle, this, &ASTUProjectile::Explode, LifeTime, false);
}

void ASTUProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	IgnoreOwner(false);
	Super::EndPlay(EndPlayReason);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CollisionComponent->OnComponentHit.RemoveDynamic(this, &ASTUProjectile::OnProjectileHit);
	Explode();
	WeaponFXComponent->PlayImpactFX(Hit);
}

void ASTUProjectile::Explode()
{
	if (!GetWorld()) { return; }
	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(),
	                                    Damage,
	                                    GetActorLocation(),
	                                    DamageRadius,
	                                    UDamageType::StaticClass(),
	                                    {GetOwner()},
	                                    this,
	                                    GetController(),
	                                    DoFullDamage);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 16, FColor::Red, false, 5.0f);
	OnExplode();
	GetWorldTimerManager().SetTimer(DestroyDelayTimerHandle, this, &ASTUProjectile::TryDestroy, DestroyDelay, false);
}

void ASTUProjectile::TryDestroy()
{
	GetWorldTimerManager().ClearTimer(DestroyDelayTimerHandle);
	GetWorldTimerManager().ClearTimer(LifeTimeTimerHandle);
	Destroy();
}

AController* ASTUProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void ASTUProjectile::IgnoreOwner(bool bShouldIgnore) const
{
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), bShouldIgnore);
	//UE_LOG(LogProjectile, Log, TEXT("Count %d"), Character->GetCapsuleComponent()->GetMoveIgnoreActors().Num());
}
