// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUPlayerHUDWidget.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> GamePauseHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> GameOverHudWidgetClass;
	
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	TMap<EMatchState, UUserWidget*> Widgets;
	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;
	virtual void DrawHUD() override;
	void DrawCrossHair();
	void HandleMatchStateChange(EMatchState MatchState);
};
