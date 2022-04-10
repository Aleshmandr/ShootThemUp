// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class USTUCharacterRespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	ASTUPlayerController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
	USTUCharacterRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void OnGamePause();
	void OnMatchStateChanged(EMatchState MatchState);
};
