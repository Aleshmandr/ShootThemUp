// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()

public:	
	ASTUBasePickup();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category="Pickup")
	float RespawnTime = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float RotationSpeed = 5.0f;
	
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	float RotationYaw;
	
	void Respawn();
	void Pickup();
	virtual bool IsApplicableTo(APawn* Pawn) const;
	void GenerateRotationYaw();
};
