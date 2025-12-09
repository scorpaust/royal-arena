// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "../RA_GameplayAbility.h"
#include "RA_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class ROYALARENA_API URA_HitReact : public URA_GameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Royal|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);

	UPROPERTY(BlueprintReadOnly, Category = "Royal|Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "Royal|Abilities")
	FVector ToInstigator;

};
