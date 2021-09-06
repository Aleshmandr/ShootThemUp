// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUSpectatorWidget.h"

#include "STUCharacterRespawnComponent.h"
#include "STUUtils.h"

bool USTUSpectatorWidget::TryGetRespawnTimer(int32& Timer) const
{
	const auto RespawnComponent = GetOwningPlayer()->FindComponentByClass<USTUCharacterRespawnComponent>();
	if (RespawnComponent != nullptr && RespawnComponent->IsRespawnInProgress())
	{
		Timer = RespawnComponent->GetRespawnTimer();
		return true;
	}
	Timer = 33;
	return false;
}
