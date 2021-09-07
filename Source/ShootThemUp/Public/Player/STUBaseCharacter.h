// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUBaseWeapon.h"
#include "STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USTUHealthComponent;
class ASTUBaseWeapon;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInitializer);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USTUHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	FName MaterialColorName = "Paint Color";


	virtual void OnDeath(const FDeathData& DeathData);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void StartShift();
	void StopShift();
	void ActivateRagdoll();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetPlayerColor(const FLinearColor& Color) const;

private:
	FTimerHandle RagdollTimerHandle;
	bool WantShift;
};
