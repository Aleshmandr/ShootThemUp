// Shoot Them Up Game. All Rights Reserved.


#include "Player/STUPlayerController.h"
#include "STUCharacterRespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTUCharacterRespawnComponent>("USTUCharacterRespawnComponent");
}
