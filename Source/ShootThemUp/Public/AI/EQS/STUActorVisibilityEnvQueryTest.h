// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "STUActorVisibilityEnvQueryTest.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUActorVisibilityEnvQueryTest : public UEnvQueryTest
{
	GENERATED_BODY()

	USTUActorVisibilityEnvQueryTest(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
