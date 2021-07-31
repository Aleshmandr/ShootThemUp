// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAIController.h"

#include "STUAICharacter.h"
#include "STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto STUCharacter = Cast<ASTUAICharacter>(InPawn);
	if (STUCharacter)
	{
		RunBehaviorTree(STUCharacter->BehaviourTree);
	}
}
