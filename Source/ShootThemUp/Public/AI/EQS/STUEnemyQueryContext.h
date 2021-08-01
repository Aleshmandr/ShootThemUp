// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "EnvironmentQuery/EnvQueryContext.h"
#include "STUEnemyQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUEnemyQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName EnemyActorKeyName = "EnemyActor";
};
