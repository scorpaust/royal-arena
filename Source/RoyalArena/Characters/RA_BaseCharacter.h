// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RA_BaseCharacter.generated.h"

/**
 * Forward declarations
 */ 
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
struct FOnAttributeChangeData;

/**
 * Delegates
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class ROYALARENA_API ARA_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ARA_BaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAttributeSet* GetAttributeSet() const {
		return nullptr;
	}

	UPROPERTY(BlueprintAssignable, Category = "Royal|Abilities")
	FASCInitialized OnASCInitialized;

	bool IsAlive() const { return bAlive; }

	void SetAlive(bool bAliveStatus) { this->bAlive = bAliveStatus; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Royal|Death")
	virtual void HandleRespawn();

protected:

	void GiveStartupAbilities();

	void InitializeAttributes() const;

	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);

	virtual void HandleDeath();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Royal|Character", meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive = true;

};
