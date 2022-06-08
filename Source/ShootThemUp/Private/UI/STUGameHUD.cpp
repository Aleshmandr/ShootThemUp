// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameHUD.h"

#include "STUGameModeBase.h"
#include "Engine/Canvas.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUHud, All, All)

void ASTUGameHUD::BeginPlay()
{
	Super::BeginPlay();
	Widgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass));
	Widgets.Add(EMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), GamePauseHudWidgetClass));
	Widgets.Add(EMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverHudWidgetClass));

	for (const auto WidgetPair : Widgets)
	{
		const auto Widget = WidgetPair.Value;
		if (Widget == nullptr) { continue; }

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::HandleMatchStateChange);
	}
}

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ASTUGameHUD::DrawCrossHair()
{
	const int CenterX = Canvas->SizeX * 0.5f;
	const int CenterY = Canvas->SizeY * 0.5f;
	const int Radius = 5;
	const int Thickness = 2;
	const FLinearColor Color = FLinearColor::Green;
	DrawLine(CenterX - Radius, CenterY, CenterX + Radius, CenterY, Color, Thickness);
	DrawLine(CenterX, CenterY - Radius, CenterX, CenterY + Radius, Color, Thickness);
}

void ASTUGameHUD::HandleMatchStateChange(const EMatchState MatchState)
{
	UE_LOG(LogSTUHud, All, TEXT("Match state changed to %s"), *UEnum::GetValueAsString(MatchState));

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Widgets.Contains(MatchState))
	{
		CurrentWidget = Widgets[MatchState];
	}

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
