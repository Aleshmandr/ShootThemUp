// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUBaseCharacter.h"
#include "STUCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTUGameModeBase();
	FOnRoundStarted OnRoundStarted;
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<ASTUBaseCharacter> AICharacterClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	FGameData GameData;

private:
	int32 CurrentRound;
	int32 CurrentRoundTimeRemain;
	FTimerHandle RoundTimerHandle;

	void SpawnBots() const;
	void StartRound();
	void UpdateTimer();
	void ResetPlayer(AController* Controller);
	void ResetPlayers();

	void CreateTeamsInfo();
	FLinearColor GetTeamColor(int32 TeamId);
	void SetPlayerColor(AController* Controller);
};
