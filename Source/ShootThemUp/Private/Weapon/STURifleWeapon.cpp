// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "STUBaseCharacter.h"
#include "GameFramework/Character.h"


void ASTURifleWeapon::StartFire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimePerShot, true);
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
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

	const FVector MuzzleLocation = GetMuzzleWorldLocation();
	if (MakeHit(HitResult, TraceStart, TraceEnd))
	{
		DrawDebugLine(GetWorld(), MuzzleLocation, HitResult.ImpactPoint, FColor::Red, false, 1.f, 0.f, 2.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 8, FColor::Red, false, 3.f, 0.f);
		MakeDamage(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), MuzzleLocation, TraceEnd, FColor::Red, false, 1.f, 0.f, 2.f);
	}
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), FMath::DegreesToRadians(ShotDirHalfAngle));
	TraceStart = ViewLocation;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}