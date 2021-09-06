// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="UI")
	bool TryGetRespawnTimer(int32& Timer) const;
	
};
