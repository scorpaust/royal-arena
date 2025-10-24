#include "RA_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void ARA_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;

	for (UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ThisClass::Primary);
	EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &ThisClass::Secondary);
	EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Started, this, &ThisClass::Tertiary);
}

void ARA_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->Jump();
}

void ARA_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->StopJumping();
}

void ARA_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void ARA_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ARA_PlayerController::Primary()
{
	// Fix: Use FGameplayTag::RequestGameplayTag to get the tag from string
	ActivateAbility(FGameplayTag::RequestGameplayTag(FName(TEXT("RATags.RAAbilities.Primary"))));
}

void ARA_PlayerController::Secondary()
{
	// Fix: Use FGameplayTag::RequestGameplayTag to get the tag from string
	ActivateAbility(FGameplayTag::RequestGameplayTag(FName(TEXT("RATags.RAAbilities.Secondary"))));
}

void ARA_PlayerController::Tertiary()
{
	// Fix: Use FGameplayTag::RequestGameplayTag to get the tag from string
	ActivateAbility(FGameplayTag::RequestGameplayTag(FName(TEXT("RATags.RAAbilities.Tertiary"))));
}

void ARA_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetCharacter());

	// Fix: Pass ASC directly to IsValid, no cast needed
	if (!IsValid(ASC)) return;

	// Add your ability activation logic here

	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

