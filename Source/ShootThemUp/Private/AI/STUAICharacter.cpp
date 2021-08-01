// Shoot Them Up Game. All Rights Reserved.


#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "STUAIController.h"

void ASTUAICharacter::OnDeath()
{
	Super::OnDeath();
	const auto AIController = Cast<ASTUAIController>(GetController());

	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}
