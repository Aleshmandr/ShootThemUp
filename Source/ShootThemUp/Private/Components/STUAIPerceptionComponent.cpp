// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUAIPerceptionComponent.h"

#include "STUAIController.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0)
	{
		return nullptr;
	}

	const auto Controller = Cast<ASTUAIController>(GetOwner());


	if (Controller == nullptr) return nullptr;
	const auto Pawn = Controller->GetPawn();
	if (Pawn == nullptr) return nullptr;
	const auto PlayerData = STUUtils::GetPlayerState(Pawn);

	float MinSqrDistance = MAX_FLT;
	AActor* NearestEnemy = nullptr;
	for (int i = 0; i < PerceivedActors.Num(); ++i)
	{
		const auto HealthComponent = PerceivedActors[i]->FindComponentByClass<USTUHealthComponent>();
		if (HealthComponent == nullptr || HealthComponent->IsDead())
		{
			continue;
		}

		const auto PerceivedPlayerData = STUUtils::GetPlayerState(PerceivedActors[i]);
		if (PerceivedPlayerData != nullptr && PlayerData != nullptr
			&& PerceivedPlayerData->GetTeamId() == PlayerData->GetTeamId())
		{
			continue;
		}

		const float SqrDistance =
			FVector::DistSquared(PerceivedActors[i]->GetActorLocation(), Pawn->GetActorLocation());
		if (SqrDistance >= MinSqrDistance) continue;

		NearestEnemy = PerceivedActors[i];
		MinSqrDistance = SqrDistance;
	}

	return NearestEnemy;
}
