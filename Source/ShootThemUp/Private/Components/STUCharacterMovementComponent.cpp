// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"

#include "GameFramework/Character.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	return IsShifting ? MaxSpeed * ShiftSpeedMultiplier : MaxSpeed;
}

float USTUCharacterMovementComponent::GetMoveDirection() const
{
	ACharacter* Character = GetCharacterOwner();
	if (Character && !Character->GetVelocity().IsZero())
	{
		const auto ForwardDir = Character->GetActorForwardVector();
		const auto VelocityDir = Character->GetVelocity().GetSafeNormal();
		const float Dot = FVector::DotProduct(ForwardDir, VelocityDir);
		const float Sign = FMath::Sign(FVector::CrossProduct(Velocity, ForwardDir).Z);
		return FMath::RadiansToDegrees( FMath::Acos(Dot)) * Sign;
	}
	return 0;
}
