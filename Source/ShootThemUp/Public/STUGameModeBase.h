// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUBaseCharacter.h"
#include "STUCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTUGameModeBase();
	FOnMatchStateChangedSignature OnMatchStateChanged;
	FOnRoundStartedSignature OnRoundStarted;
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	int32 GetCurrentRound() const { return CurrentRound; }
	int32 GetRoundsCount() const { return GameData.RoundsNum; }
	int32 GetCurrentRoundTimeRemain() const { return CurrentRoundTimeRemain; }
	void RequestRespawn(AController* Controller);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<ASTUBaseCharacter> AICharacterClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	FGameData GameData;

private:
	EMatchState MatchState = EMatchState::WaitingToStart;
	int32 CurrentRound;
	int32 CurrentRoundTimeRemain;
	FTimerHandle RoundTimerHandle;

	void SpawnBots() const;
	void StartRound();
	void UpdateTimer();
	void ResetPlayer(AController* Controller);
	void ResetPlayers();
	void RespawnPlayer(const AController* Controller) const;

	void CreateTeamsInfo();
	FLinearColor GetTeamColor(int32 TeamId);
	void SetPlayerColor(AController* Controller) const;
	void TrackPlayer(AController* Controller) const;
	void GameOver();
	
	void LogPlayers() const;
	void HandlePlayerDeath(const FDeathData& DeathData) const;
	void SetMatchState(EMatchState NewMatchState);
};
