// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RA_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROYALARENA_API URA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Royal|Debug")
	bool bDrawDebugs = false;
};
