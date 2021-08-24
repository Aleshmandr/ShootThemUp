// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAIController.h"

#include "STUAICharacter.h"
#include "STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTUAIController::ASTUAIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
	RespawnComponent = CreateDefaultSubobject<USTUCharacterRespawnComponent>("USTUCharacterRespawnComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);
	
	bWantsPlayerState = true;
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

void ASTUAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto EnemyActor = GetEnemyActor();
	SetFocus(EnemyActor);
}

AActor* ASTUAIController::GetEnemyActor()
{
	const auto BlackboardComponent = GetBlackboardComponent();
	if(!BlackboardComponent) return nullptr;

	return  Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyBlackboardKey));;
}
