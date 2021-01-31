// Shoot Them Up Game. All Rights Reserved.


#include "STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacter, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Pressed, this, &ASTUBaseCharacter::StartShift);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Released, this, &ASTUBaseCharacter::StopShift);
}

void ASTUBaseCharacter::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void ASTUBaseCharacter::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

void ASTUBaseCharacter::StartShift()
{
	if (GetCharacterMovement())
	{
		IsShifting = true;
		DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = ShiftSpeed;
	}
}

void ASTUBaseCharacter::StopShift()
{
	if (GetCharacterMovement())
	{
		IsShifting = false;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}
