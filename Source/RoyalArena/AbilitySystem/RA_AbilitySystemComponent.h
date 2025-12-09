// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RA_AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ROYALARENA_API URA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(BlueprintCallable, Category = "Royal|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = "Royal|Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 LevelToAdd = 1);

private:

	void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};
