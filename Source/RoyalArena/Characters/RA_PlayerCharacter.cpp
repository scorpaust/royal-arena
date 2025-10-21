// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include <RoyalArena/Player/RA_PlayerState.h>

ARA_PlayerCharacter::ARA_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;

	bUseControllerRotationYaw = false;

	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;

	GetCharacterMovement()->AirControl = 0.35f;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;

	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character

	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

UAbilitySystemComponent* ARA_PlayerCharacter::GetAbilitySystemComponent() const
{
	// Use the public accessor, not direct member access
	ARA_PlayerState* RAPlayerState = Cast<ARA_PlayerState>(GetPlayerState());

	if (!IsValid(RAPlayerState)) return nullptr;	

	return RAPlayerState->GetAbilitySystemComponent();
}

void ARA_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!IsValid(GetAbilitySystemComponent())) return;

	// Fix: Cast GetPlayerState() to AActor* for InitAbilityActorInfo
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, Cast<AActor>(GetPlayerState()));
}

void ARA_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent())) return;

	// Fix: Cast GetPlayerState() to AActor* for InitAbilityActorInfo
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, Cast<AActor>(GetPlayerState()));
}
