// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "../Characters/RA_BaseCharacter.h"
#include "RA_EnemyCharacter.generated.h"

/**
* Forward Declarations
*/

class URA_AbilitySystemComponent;
class UAttributeSet;
class URA_AttributeSet;

/**
 * 
 */
UCLASS()
class ROYALARENA_API ARA_EnemyCharacter : public ARA_BaseCharacter
{
	GENERATED_BODY()

public:

	ARA_EnemyCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAttributeSet* GetAttributeSet() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Royal|AI")
	float AcceptanceRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Royal|AI")
	float MinAttackDelay = .1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Royal|AI")
	float MaxAttackDelay = .5f;

protected:

	virtual void BeginPlay() override;

	virtual void HandleDeath() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URA_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<URA_AttributeSet> AttributeSet;
};
