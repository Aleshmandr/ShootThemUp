// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	int32 GetTeamId() const { return TeamId; }
	void SetTeamId(int32 Id) { TeamId = Id; }

	FLinearColor GetTeamColor() const { return TeamColor; }
	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }

	void AddKill() { Kills++; }
	void AddDeath() { Deaths++; }

	int32 GetKills() const { return Kills; }
	int32 GetDeaths() const { return Deaths; }
	void LogPlayerState();

private:
	int32 TeamId;
	FLinearColor TeamColor;
	int32 Kills;
	int32 Deaths;
};
