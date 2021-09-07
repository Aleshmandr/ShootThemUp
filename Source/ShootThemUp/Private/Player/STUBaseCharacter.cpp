// Shoot Them Up Game. All Rights Reserved.

#include "STUBaseCharacter.h"
#include "STUCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacter, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInitializer): Super(
	ObjInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("Health");
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("Weapon");
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(GetMesh());
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& Color) const
{
	const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (MaterialInstance == nullptr) return;
	
	MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

void ASTUBaseCharacter::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
	USTUCharacterMovementComponent* MoveComponent = Cast<USTUCharacterMovementComponent>(GetMovementComponent());
	if (MoveComponent)
	{
		MoveComponent->IsShifting = WantShift && Axis > 0;
	}
}

void ASTUBaseCharacter::MoveRight(float Axis)
{
	USTUCharacterMovementComponent* MoveComponent = Cast<USTUCharacterMovementComponent>(GetMovementComponent());
	if (MoveComponent && MoveComponent->IsShifting)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), Axis);
}

void ASTUBaseCharacter::StartShift()
{
	WantShift = true;
}

void ASTUBaseCharacter::StopShift()
{
	WantShift = false;
	USTUCharacterMovementComponent* MoveComponent = Cast<USTUCharacterMovementComponent>(GetMovementComponent());
	if (MoveComponent)
	{
		MoveComponent->IsShifting = false;
	}
}

void ASTUBaseCharacter::OnDeath(const FDeathData& DeathData)
{
	UE_LOG(LogCharacter, Log, TEXT("Player %s is dead"), *GetName());
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(10);
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponComponent->StopFire();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetWorldTimerManager().SetTimer(RagdollTimerHandle, this, &ASTUBaseCharacter::ActivateRagdoll, 0.3f, false);
}

void ASTUBaseCharacter::ActivateRagdoll()
{
	GetMesh()->SetSimulatePhysics(true);
}
