// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUHealthComponent();

	float GetHealth() const { return Health; }
protected:
	UPROPERTY(EditDefaultsOnly, Category= "Health", BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1000))
	float MaxHealth = 100.f;
	virtual void BeginPlay() override;

private:
	float Health = 0.f;
	
	UFUNCTION()
    void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};