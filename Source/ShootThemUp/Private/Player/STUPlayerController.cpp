// Shoot Them Up Game. All Rights Reserved.


#include "Player/STUPlayerController.h"
#include "STUCharacterRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTUCharacterRespawnComponent>("USTUCharacterRespawnComponent");
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
