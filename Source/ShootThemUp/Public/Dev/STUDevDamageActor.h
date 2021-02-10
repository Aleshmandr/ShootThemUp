// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	ASTUDevDamageActor();


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
