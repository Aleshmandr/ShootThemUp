// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUGameDataWidget.h"

int32 USTUGameDataWidget::GetCurrentRound() const
{
	const auto STUGameMode = GetCurrentGameMode();
	return STUGameMode == nullptr ? 0 : STUGameMode->GetCurrentRound();
}

int32 USTUGameDataWidget::GetRoundsCount() const
{
	const auto STUGameMode = GetCurrentGameMode();
	return STUGameMode == nullptr ? 0 : STUGameMode->GetRoundsCount();
}

int32 USTUGameDataWidget::GetRoundTimer() const
{
	const auto STUGameMode = GetCurrentGameMode();
	return STUGameMode == nullptr ? 0 : STUGameMode->GetCurrentRoundTimeRemain();
}

ASTUGameModeBase* USTUGameDataWidget::GetCurrentGameMode() const
{
	return GetWorld() == nullptr ? nullptr : Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
}
