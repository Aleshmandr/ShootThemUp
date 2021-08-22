// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetNormalizedHealth() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	bool TryHeal(float HealAmount);

protected:
	UPROPERTY(EditDefaultsOnly, Category= "Health", BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1000))
	float MaxHealth = 100.f;
	UPROPERTY(EditDefaultsOnly, Category= "Heal", BlueprintReadWrite)
	bool AutoHeal = false;
	UPROPERTY(EditDefaultsOnly, Category= "Heal", BlueprintReadWrite, meta = (EditCondition = "AutoHeal"))
	float AutoHealDelay = 3.f;
	UPROPERTY(EditDefaultsOnly, Category= "Heal", BlueprintReadWrite, meta = (EditCondition = "AutoHeal"))
	float AutoHealUpdateDelta = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category= "Heal", BlueprintReadWrite, meta = (EditCondition = "AutoHeal"))
	float AutoHealValue = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Damage")
	FVector2D LandedDamageVelocity = FVector2D(800.0f, 1200.0f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;
	float Health = 0.f;
	float HealTimer = 0.f;

	void SetHealth(float NewHealth);

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                         AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION()
	void OnLanded(const FHitResult& Hit);

	void PlayCameraShake() const;
};
