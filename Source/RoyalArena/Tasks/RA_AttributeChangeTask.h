// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayEffectAggregator.h" // For FGameplayAttribute
#include "RA_AttributeChangeTask.generated.h"

// Naming convention: Unreal Engine delegates should be prefixed with 'F' and use PascalCase.
// The parameter names should use PascalCase as well, matching the .editorconfig Unreal Engine style.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

/*
Forward declarations
*/

struct FOnAttributeChangeData;
class UAbilitySystemComponent;

UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class ROYALARENA_API URA_AttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Royal Arena|Tasks")
	static URA_AttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	UFUNCTION(BlueprintCallable)
	void EndTask();

	void AttributeChanged(const FOnAttributeChangeData& Data);

	TWeakObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayAttribute AttributeToListenFor;
};
