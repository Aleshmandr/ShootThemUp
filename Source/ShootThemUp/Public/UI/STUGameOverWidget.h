// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUGameOverWidget.generated.h"

class USTUPlayerStatRowWidget;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<USTUPlayerStatRowWidget> PlayerStatWidgetClass;
	
private:
	void HandleMatchStateChange(EMatchState MatchState);
	void UpdatePlayersStat();
};
