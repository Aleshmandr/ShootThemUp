// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerNameText(const FText& Name);
	void SetKillsText(const FText& Kills);
	void SetDeathsText(const FText& Deaths);
	void SetTeamText(const FText& Deaths);
	void SetHighlightVisible(const bool Visible);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* KillsText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DeathsText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TeamText;
	
	UPROPERTY(meta=(BindWidget))
	UImage* HighlightImage;
	
};
