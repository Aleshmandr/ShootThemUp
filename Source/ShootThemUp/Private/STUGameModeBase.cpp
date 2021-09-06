// Shoot Them Up Game. All Rights Reserved.


#include "STUGameModeBase.h"

#include "AIController.h"
#include "STUBaseCharacter.h"
#include "STUCharacterRespawnComponent.h"
#include "STUHealthComponent.h"
#include "UI/STUGameHUD.h"
#include "STUPlayerController.h"
#include "STUPlayerState.h"
#include "STUUtils.h"

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
		LogPlayers();
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

void ASTUGameModeBase::RequestRespawn(AController* Controller)
{
	ResetPlayer(Controller);
}

void ASTUGameModeBase::RespawnPlayer(const AController* Controller) const
{
	if (!Controller) { return; }

	if (CurrentRoundTimeRemain - GameData.RespawnTime < GameData.RoundEndRespawnThresh) { return; }

	const auto RespawnComponent = Controller->FindComponentByClass<USTUCharacterRespawnComponent>();

	if (!RespawnComponent) { return; }

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTUGameModeBase::ResetPlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
	SetPlayerColor(Controller);
	TrackPlayer(Controller);
}

void ASTUGameModeBase::TrackPlayer(AController* Controller) const
{
	if (Controller == nullptr) { return; }

	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
	if (HealthComponent == nullptr) { return; }

	HealthComponent->OnDeath.AddUObject(this, &ASTUGameModeBase::HandlePlayerDeath);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamId = 0;
	for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
	{
		const auto Controller = Iterator->Get();
		if (Controller == nullptr) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
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

void ASTUGameModeBase::SetPlayerColor(AController* Controller) const
{
	if (Controller == nullptr) return;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if (PlayerState == nullptr) return;

	const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
	if (Character == nullptr) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::LogPlayers() const
{
	if (!GetWorld()) return;

	for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
	{
		const auto Controller = Iterator->Get();
		if (Controller == nullptr) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (PlayerState == nullptr) continue;

		PlayerState->LogPlayerState();
	}
}

void ASTUGameModeBase::HandlePlayerDeath(const FDeathData& DeathData) const
{
	if (!GetWorld()) return;

	if (DeathData.InstigatedBy != nullptr)
	{
		const auto KillerState = STUUtils::GetPlayerState(DeathData.InstigatedBy->GetPawn());
		if (KillerState != nullptr)
		{
			KillerState->AddKill();
		}
	}

	if (DeathData.KilledActor != nullptr)
	{
		const auto VictimState = STUUtils::GetPlayerState(DeathData.KilledActor);
		if (VictimState != nullptr)
		{
			VictimState->AddDeath();
		}
		RespawnPlayer(DeathData.KilledController);
	}
}
