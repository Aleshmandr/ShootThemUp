// Shoot Them Up Game. All Rights Reserved.

#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPickup, All, All)

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->InitSphereRadius(50.0f);
	SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);
	Respawn();
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogPickup, Display, TEXT("Pickup overlap"));

	const auto Pawn = Cast<APawn>(OtherActor);
	if (IsApplicableTo(Pawn))
	{
		Pickup();
	}
}


void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationYaw, 0));
}

void ASTUBasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}


void ASTUBasePickup::Pickup()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

bool ASTUBasePickup::IsApplicableTo(APawn* Pawn) const
{
	return false;
}

void ASTUBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1 : -1;
	RotationYaw = RotationSpeed * Direction;
}
