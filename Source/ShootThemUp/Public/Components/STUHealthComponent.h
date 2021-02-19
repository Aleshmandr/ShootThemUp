// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	USTUHealthComponent();

	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

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

	virtual void BeginPlay() override;


private:
	float Health = 0.f;
	float HealTimer = 0.f;

	void SetHealth(float NewHealth);

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                         AController* InstigatedBy, AActor* DamageCauser);
};
