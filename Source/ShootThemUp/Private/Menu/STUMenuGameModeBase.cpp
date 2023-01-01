// Shoot Them Up Game. All Rights Reserved.


#include "Menu/STUMenuGameModeBase.h"

#include "STUMenuHUD.h"
#include "STUMenuPlayerController.h"

void ASTUMenuGameModeBase::STUMenuGameModeBase()
{
	PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
	HUDClass = ASTUMenuHUD::StaticClass();
}
