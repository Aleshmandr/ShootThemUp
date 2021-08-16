// Shoot Them Up Game. All Rights Reserved.


#include "STUGameModeBase.h"

#include "AIController.h"
#include "STUBaseCharacter.h"
#include "UI/STUGameHUD.h"
#include "STUPlayerController.h"
#include "STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All)

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();
	SpawnBots();
	CreateTeamsInfo();
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

void ASTUGameModeBase::SpawnBots() const
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		GetWorld()->SpawnActor<AAIController>(AIControllerClass);
	}
}

void ASTUGameModeBase::StartRound()
{
	CurrentRound ++;
	CurrentRoundTimeRemain = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASTUGameModeBase::UpdateTimer, 1, true);
	ResetPlayers();
	UE_LOG(LogSTUGameModeBase, All, TEXT("Round %i started"), CurrentRound);
	OnRoundStarted.Broadcast(CurrentRound);
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

void ASTUGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
	{
		ResetPlayer(Iterator->Get());
	}
}

void ASTUGameModeBase::ResetPlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamId = 0;
	for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
	{
		const auto Controller = Iterator->Get();
		if (Controller == nullptr) continue;

		auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (PlayerState == nullptr) continue;

		TeamId = (++TeamId) % GameData.TeamsCount;
		PlayerState->SetTeamId(TeamId);
		PlayerState->SetTeamColor(GetTeamColor(TeamId));
	}
}

FLinearColor ASTUGameModeBase::GetTeamColor(int32 TeamId)
{
	if (GameData.TeamColors.IsValidIndex(TeamId))
	{
		return GameData.TeamColors[TeamId];
	}

	return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
	if(Controller == nullptr) return;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if(PlayerState == nullptr) return;

	auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
	if(Character == nullptr) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}
