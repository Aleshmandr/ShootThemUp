// Shoot Them Up Game. All Rights Reserved.


#include "STUGameModeBase.h"

#include "AIController.h"
#include "STUBaseCharacter.h"
#include "UI/STUGameHUD.h"
#include "STUPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All)

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();
	SpawnBots();
	CurrentRound = 0;
	StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA(AAIController::StaticClass()))
	{
		return AICharacterClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass);
		RestartPlayer(AIController);
	}
}

void ASTUGameModeBase::StartRound()
{
	CurrentRound ++;
	CurrentRoundTimeRemain = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASTUGameModeBase::UpdateTimer, 1, true);
	UE_LOG(LogSTUGameModeBase, All, TEXT("Round %i started"), CurrentRound);
}

void ASTUGameModeBase::UpdateTimer()
{
	if (--CurrentRoundTimeRemain <= 0)
	{
		GetWorldTimerManager().ClearTimer(RoundTimerHandle);
		if (CurrentRound >= GameData.RoundsNum)
		{
			UE_LOG(LogSTUGameModeBase, All, TEXT("End game"));
		}
		else
		{
			StartRound();
		}
	}
}
