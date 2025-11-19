// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "../Characters/RA_BaseCharacter.h"
#include "RA_EnemyCharacter.generated.h"

/**
* Forward Declarations
*/

class URA_AbilitySystemComponent;

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
	
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URA_AbilitySystemComponent> AbilitySystemComponent;
};
