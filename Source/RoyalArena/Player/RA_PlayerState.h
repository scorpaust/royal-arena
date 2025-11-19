// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RA_PlayerState.generated.h"

/**
 * Forward Declarations
 */

class URA_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class ROYALARENA_API ARA_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ARA_PlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Royal|Abilities")
	TObjectPtr<URA_AbilitySystemComponent> AbilitySystemComponent;
};
