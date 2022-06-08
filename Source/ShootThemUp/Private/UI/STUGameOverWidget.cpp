// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameOverWidget.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"
#include "STUUtils.h"
#include "Components/VerticalBox.h"

bool USTUGameOverWidget::Initialize()
{
	if (const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::HandleMatchStateChange);
	}
	return Super::Initialize();
}

void USTUGameOverWidget::HandleMatchStateChange(EMatchState MatchState)
{
	if(MatchState == EMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void USTUGameOverWidget::UpdatePlayersStat()
{
	if (!GetWorld()) return;

	PlayerStatBox->ClearChildren();

	for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
	{
		const auto Controller = Iterator->Get();
		if(!Controller)
		{
			continue;
		}

		const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
		if(!PlayerState)
		{
			continue;
		}

		const auto PlayerStatWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatWidgetClass);
		if(!PlayerStatWidget)
		{
			continue;
		}
		PlayerStatWidget->SetPlayerNameText(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatWidget->SetKillsText(STUUtils::IntToFString(PlayerState->GetKills()));
		PlayerStatWidget->SetDeathsText(STUUtils::IntToFString(PlayerState->GetDeaths()));
		PlayerStatWidget->SetTeamText(STUUtils::IntToFString(PlayerState->GetTeamId()));
		PlayerStatWidget->SetHighlightVisible(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatWidget);
	}
}
