// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RA_WidgetComponent.generated.h"

/**
 * Forward Declarations
 */

class ARA_BaseCharacter;
class URA_AbilitySystemComponent;
class URA_AttributeSet;

/**
 * 
 */
UCLASS()
class ROYALARENA_API URA_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:

	TWeakObjectPtr<ARA_BaseCharacter> RoyalCharacter;

	TWeakObjectPtr<URA_AbilitySystemComponent> AbilitySystemComponent;
		
	TWeakObjectPtr<URA_AttributeSet> AttributeSet;

	void InitAbilitySystemData();

	bool IsASCInitialized() const;

	void InitializeAttributeDelegate();

	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute> &Pair);

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
};
