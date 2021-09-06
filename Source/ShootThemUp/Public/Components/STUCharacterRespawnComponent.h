// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCharacterRespawnComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUCharacterRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUCharacterRespawnComponent();

	void Respawn(int32 Timer);
	
	int32 GetRespawnTimer() const { return RespawnTimer; }

	bool IsRespawnInProgress() const;

private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnTimer;

	void UpdateTimer();
};
