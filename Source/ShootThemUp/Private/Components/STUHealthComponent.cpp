// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUHealthComponent.h"

#include "STUFireDamageType.h"
#include "STUIceDamageType.h"
#include "GameFramework/Character.h"

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
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	check(OwnerCharacter);
	OwnerCharacter->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::HandleTakeAnyDamage);
	OwnerCharacter->LandedDelegate.AddDynamic(this, &USTUHealthComponent::OnLanded);
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

void USTUHealthComponent::OnLanded(const FHitResult& Hit)
{
	const float LandingVelocity = -OwnerCharacter->GetVelocity().Z;
	UE_LOG(LogHealth, Log, TEXT("Landing velocity = %f"), LandingVelocity);
	if (LandingVelocity >= LandedDamageVelocity.X)
	{
		const float NormDamageVelocity = FMath::Clamp(LandingVelocity, LandedDamageVelocity.X, LandedDamageVelocity.Y) /
			LandedDamageVelocity.Y;
		const float Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, LandingVelocity);
		UE_LOG(LogHealth, Log, TEXT("Landing damage = %f"), Damage);
		OwnerCharacter->TakeDamage(Damage, FDamageEvent{}, nullptr, nullptr);
	}
}
