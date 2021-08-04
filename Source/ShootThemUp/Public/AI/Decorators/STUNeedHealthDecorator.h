// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUNeedHealthDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUNeedHealthDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USTUNeedHealthDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float NormalizedHealthThresh = 0.5f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
