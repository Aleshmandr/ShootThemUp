// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STUMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();
	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}
}

void USTUMenuWidget::OnStartGame()
{
	if(!GetWorld())
	{
		return;
	}

	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if(!GameInstance )
	{
		return;
	}
	
	if(GameInstance->GetStartLevelName().IsNone())
	{
		UE_LOG(LogSTUMenuWidget, Error, TEXT("Empty start level name!"));
		return;
	}
	
	UGameplayStatics::OpenLevel(this, GameInstance->GetStartLevelName());
}
