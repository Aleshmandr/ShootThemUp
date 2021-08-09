// Shoot Them Up Game. All Rights Reserved.


#include "STUGameModeBase.h"

#include "AIController.h"
#include "STUBaseCharacter.h"
#include "UI/STUGameHUD.h"
#include "STUPlayerController.h"

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
