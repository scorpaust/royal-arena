// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RA_BaseCharacter.generated.h"


UCLASS(Abstract)
class ROYALARENA_API ARA_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ARA_BaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};
