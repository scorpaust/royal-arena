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

	URA_AbilitySystemComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:

	virtual void BeginPlay() override;
};
