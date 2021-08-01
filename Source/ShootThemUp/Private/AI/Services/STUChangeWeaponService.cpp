// Shoot Them Up Game. All Rights Reserved.


#include "AI/Services/STUChangeWeaponService.h"

#include "AIController.h"
#include "STUWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "ChangeWeapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const float RandValue = FMath::FRand();
	if (RandValue <= ChangeProbability)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		if (Controller == nullptr) return;
		const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();
		if (WeaponComponent == nullptr) return;
		
		WeaponComponent->TryEquipNonEmptyWeapon();
	}
}
