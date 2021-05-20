// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameHUD.h"

#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
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
