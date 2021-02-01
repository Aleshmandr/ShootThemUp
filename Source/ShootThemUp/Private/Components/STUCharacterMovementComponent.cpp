// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"

#include "STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(GetCharacterOwner());
	const float MaxSpeed = Super::GetMaxSpeed();
	return Character && Character->IsShifting ? MaxSpeed * ShiftSpeedMultiplier : MaxSpeed;
}
