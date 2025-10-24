// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h" // Add this if not present
#include "RA_PlayerController.generated.h"

/**
 * Forward declarations
 */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class ROYALARENA_API ARA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditDefaultsOnly, Category="Royal|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Input|Movement")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Input|Abilities")
	TObjectPtr<UInputAction> SecondaryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Input|Abilities")
	TObjectPtr<UInputAction> TertiaryAction;

	void Jump();

	void StopJumping();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Primary();

	void Secondary();

	void Tertiary();

	void ActivateAbility(const FGameplayTag& AbilityTag) const;
};
