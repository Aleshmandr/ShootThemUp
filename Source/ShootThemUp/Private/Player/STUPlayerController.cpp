// Shoot Them Up Game. All Rights Reserved.


#include "Player/STUPlayerController.h"
#include "STUCharacterRespawnComponent.h"
#include "STUGameModeBase.h"
#include "GameFramework/GameModeBase.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTUCharacterRespawnComponent>("USTUCharacterRespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
		}
	}
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) { return; }

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnGamePause);
}

void ASTUPlayerController::OnGamePause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) { return; }

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(EMatchState MatchState)
{
	switch (MatchState)
	{
	case EMatchState::InProgress:
	case EMatchState::WaitingToStart:
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
		break;
	case EMatchState::Pause:
	case EMatchState::GameOver:
	default:
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
