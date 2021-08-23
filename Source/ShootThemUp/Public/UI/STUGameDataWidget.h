// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetCurrentRound() const;
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetRoundsCount() const;
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetRoundTimer() const;
	private:
	ASTUGameModeBase* GetCurrentGameMode() const;
};
