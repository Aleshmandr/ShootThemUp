// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STUMenuHUD.h"

void ASTUMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if(const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass))
	{
		MenuWidget->AddToViewport();
	}
}
