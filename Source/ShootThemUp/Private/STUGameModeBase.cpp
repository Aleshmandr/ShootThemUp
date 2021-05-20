// Shoot Them Up Game. All Rights Reserved.


#include "STUGameModeBase.h"
#include "STUBaseCharacter.h"
#include "UI/STUGameHUD.h"
#include "STUPlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}
