// Dinis Miguel Costa - Todos os direitos reservados

#pragma once

#include "CoreMinimal.h"
#include "../RA_GameplayAbility.h"
#include "RA_Primary.generated.h"

/**
 * 
 */
UCLASS()
class ROYALARENA_API URA_Primary : public URA_GameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Royal|Abilities")
	TArray<AActor*> HitBoxOverlapTest();

	UFUNCTION(BlueprintCallable, Category = "Royal|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& ActorsHit);

private:

	void DrawHitboxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitboxLocation) const;	

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Abilities", meta = (AllowPrivateAccess = "true"))
	float HitBoxRadius = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Abilities", meta = (AllowPrivateAccess = "true"))
	float HitBoxForwardOffset = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Royal|Abilities", meta = (AllowPrivateAccess = "true"))
	float HitBoxElevationOffset = 20.f;
	
};
