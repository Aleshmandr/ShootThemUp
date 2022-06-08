// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerNameText(const FText& Name)
{
	if(!PlayerNameText)
	{
		return;
	}
	PlayerNameText->SetText(Name);
}

void USTUPlayerStatRowWidget::SetKillsText(const FText& Kills)
{
	if(!KillsText)
	{
		return;
	}
	KillsText->SetText(Kills);
}

void USTUPlayerStatRowWidget::SetDeathsText(const FText& Deaths)
{
	if(!DeathsText)
	{
		return;
	}
	DeathsText->SetText(Deaths);
}

void USTUPlayerStatRowWidget::SetTeamText(const FText& Deaths)
{
	if(!TeamText)
	{
		return;
	}
	TeamText->SetText(Deaths);
}

void USTUPlayerStatRowWidget::SetHighlightVisible(const bool Visible)
{
	if(!HighlightImage)
	{
		return;
	}
	HighlightImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
