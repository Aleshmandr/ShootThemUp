// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STUBaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "STUBaseCharacter.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All)

ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void ASTUBaseWeapon::StartFire()
{
}

void ASTUBaseWeapon::StopFire()
{
}

void ASTUBaseWeapon::MakeShot()
{
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return nullptr;
	}
	return Character->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	APlayerController* Controller = GetPlayerController();
	if (!Controller)
	{
		return false;
	}
	
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	const FVector ShootDirection = ViewRotation.Vector();
	TraceStart = ViewLocation;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

bool ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}
