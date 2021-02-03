// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsShifting;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta = (ClampMin = "1"))
	float ShiftSpeedMultiplier = 2.f;

	virtual float GetMaxSpeed() const override;
};
