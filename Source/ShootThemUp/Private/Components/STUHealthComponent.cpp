// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUHealthComponent.h"

#include "STUFireDamageType.h"
#include "STUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealth, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	AActor* Actor = GetOwner();
	if (Actor)
	{
		Actor->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::HandleTakeAnyDamage);
	}
}

void USTUHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                              AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogHealth, Log, TEXT("HandleTakeAnyDamage %f"), Damage);
	Health -= Damage;
	if (DamageType != nullptr)
	{
		if (DamageType->IsA<USTUFireDamageType>())
		{
			UE_LOG(LogHealth, Log, TEXT("Fire damage"));
		}
		else if (DamageType->IsA<USTUIceDamageType>())
		{
			UE_LOG(LogHealth, Log, TEXT("Ice damage"));
		}
	}
}
