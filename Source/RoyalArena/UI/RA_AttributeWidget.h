// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../AbilitySystem/RA_AttributeSet.h"
#include "RA_AttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROYALARENA_API URA_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Royal|Attribute")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Royal|Attribute")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, URA_AttributeSet* AttributeSet);

	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Changed"), Category = "Royal|Attribute")
	void BP_OnAttributeChanged(float NewValue, float NewMaxValue);	
}; 
