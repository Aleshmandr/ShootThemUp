// Shoot Them Up Game. All Rights Reserved.

#include "STUBaseCharacter.h"
#include "STUCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("Health");
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthText");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("Weapon");
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	OnHealthChanged(HealthComponent->GetHealth());
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Pressed, this, &ASTUBaseCharacter::StartShift);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Released, this, &ASTUBaseCharacter::StopShift);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
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

void ASTUBaseCharacter::OnDeath()
{
	UE_LOG(LogCharacter, Log, TEXT("Player %s is dead"), *GetName());
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5);
	Controller->ChangeState(NAME_Spectating);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ASTUBaseCharacter::OnHealthChanged(float Health) const
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}
