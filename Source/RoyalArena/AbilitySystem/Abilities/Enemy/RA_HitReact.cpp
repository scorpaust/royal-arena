// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_HitReact.h"

void URA_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();

	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();

	const FVector InstigatorLocation = Instigator ? Instigator->GetActorLocation() : FVector::ZeroVector;

	ToInstigator = InstigatorLocation - AvatarLocation;

	ToInstigator.Normalize();
}
