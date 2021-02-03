// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	return IsShifting ? MaxSpeed * ShiftSpeedMultiplier : MaxSpeed;
}
