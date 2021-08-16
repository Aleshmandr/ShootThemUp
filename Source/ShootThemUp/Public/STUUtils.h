#pragma once
#include "STUPlayerState.h"

class STUUtils
{
public:
	template <typename T>
	static T* GetSTUPlayerComponent(APawn* PlayerPawn)
	{
		if (PlayerPawn == nullptr) return nullptr;
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}

	static ASTUPlayerState* GetPlayerData(AActor* Actor)
	{
		if (Actor == nullptr) return nullptr;

		const auto Pawn = Cast<APawn>(Actor);
		if (Pawn == nullptr) return nullptr;

		return Cast<ASTUPlayerState>(Pawn->GetPlayerState());
	}
};
