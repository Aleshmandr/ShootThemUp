// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUHealthComponent.h"

#include "STUFireDamageType.h"
#include "STUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealth, All, All)

void USTUHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	if (!AutoHeal || IsDead())
	{
		return;
	}
	HealTimer -= DeltaTime;
	if (Health < MaxHealth && HealTimer <= 0)
	{
		SetHealth(Health + AutoHealValue);
		HealTimer = AutoHealUpdateDelta;
	}
}

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	AActor* Actor = GetOwner();
	if (Actor)
	{
		Actor->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::HandleTakeAnyDamage);
	}
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void USTUHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                              AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || IsDead())
	{
		return;
	}
	UE_LOG(LogHealth, Log, TEXT("HandleTakeAnyDamage %f"), Damage);
	HealTimer = AutoHealDelay;
	SetHealth(Health - Damage);
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
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}
