// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPauseWidget.h"

#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool USTUPauseWidget::Initialize()
{
	const bool InitStatus = Super::Initialize();
	if (ClearPauseButton != nullptr)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
	}
	return InitStatus;
}

void USTUPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) { return; }

	GetWorld()->GetAuthGameMode()->ClearPause();
}
