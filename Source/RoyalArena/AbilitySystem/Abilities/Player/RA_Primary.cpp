// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_Primary.h"
#include "Engine/OverlapResult.h"
#include "AbilitySystemBlueprintLibrary.h"


TArray<AActor*> URA_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;

	ResponseParams.CollisionResponse.SetAllChannels(ECollisionResponse::ECR_Ignore);

	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;

	FCollisionShape SphereShape = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;

	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);

	GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECC_Visibility,
		SphereShape,
		QueryParams,
		ResponseParams
	);

	TArray<AActor*> ActorsHit;

	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) continue;

		ActorsHit.AddUnique(Result.GetActor());
	}

	if (bDrawDebugs)
	{
		DrawHitboxOverlapDebugs(OverlapResults, Location);
	}

	return ActorsHit;
}

void URA_Primary::SendHitReactEventToActors(const TArray<AActor*>& ActorsHit)
{
	for (AActor* HitActor : ActorsHit)
	{
		if (IsValid(HitActor))
		{
			FGameplayTag RATag_HitReact = FGameplayTag::RequestGameplayTag(FName("RATags.Events.Enemy.HitReact"));

			FGameplayEventData Payload;

			Payload.Instigator = GetAvatarActorFromActorInfo();

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				HitActor,
				RATag_HitReact,
				Payload
			);
		}

	}
}

void URA_Primary::DrawHitboxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitboxLocation) const
{
	DrawDebugSphere(GetWorld(), HitboxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);

	for (const FOverlapResult& Result : OverlapResults)
	{
		if (IsValid(Result.GetActor()))
		{
			FVector DebugLocation = Result.GetActor()->GetActorLocation();

			DebugLocation.Z += 100.f;

			DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 10, FColor::Green, false, 3.f);
		}
	}
}
