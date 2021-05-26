// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASTUBaseWeapon();
	virtual void Fire();
	void MakeShot();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;

	virtual void BeginPlay() override;
	

	private:
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	bool MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	FVector GetMuzzleWorldLocation() const;
	void MakeDamage(const FHitResult& HitResult);
};
