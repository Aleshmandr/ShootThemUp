// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STULauncherWeapon.h"
#include "STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
	MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{

	if (!GetWorld())
	{
		return;
	}

	FVector TraceStart;
	FVector TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	FVector EndPoint = HitResult.bBlockingHit ?  HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if(Projectile)
	{
		Projectile->SetDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}	
}
