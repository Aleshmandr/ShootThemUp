// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All);

void ASTUPlayerState::LogPlayerState()
{
	UE_LOG(LogSTUPlayerState, Display, TEXT("Name: %s, Kills: %i, Deaths: %i"), *GetName(), Kills, Deaths);
}
