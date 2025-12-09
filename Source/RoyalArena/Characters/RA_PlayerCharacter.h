// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "RA_BaseCharacter.h"
#include "RA_PlayerCharacter.generated.h"

/**
 * Forward declarations
 */

class USpringArmComponent;
class UCameraComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class ROYALARENA_API ARA_PlayerCharacter : public ARA_BaseCharacter
{
	GENERATED_BODY()

public:
	
	ARA_PlayerCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual UAttributeSet* GetAttributeSet() const override;

private:

	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

};
