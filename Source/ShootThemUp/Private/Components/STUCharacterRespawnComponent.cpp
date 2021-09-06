// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUCharacterRespawnComponent.h"

#include "STUGameModeBase.h"

USTUCharacterRespawnComponent::USTUCharacterRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUCharacterRespawnComponent::Respawn(int32 Timer)
{
	if (!GetWorld() || GetWorld()->GetTimerManager().TimerExists(RespawnTimerHandle)) { return; }

	RespawnTimer = Timer;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTUCharacterRespawnComponent::UpdateTimer, 1.0f,
	                                       true);
}

bool USTUCharacterRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USTUCharacterRespawnComponent::UpdateTimer()
{
	if (!GetWorld()) { return; }

	if (--RespawnTimer <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->RequestRespawn(Cast<AController>(GetOwner()));
	}
}
