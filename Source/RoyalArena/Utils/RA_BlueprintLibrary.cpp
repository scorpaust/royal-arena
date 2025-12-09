// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_BlueprintLibrary.h"

EHitDirection URA_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);

	if (Dot < -.5f)
	{
		return EHitDirection::Back;
	}

	if (Dot < .5f)
	{
		// Either left or right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);

		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		else
		{
			return EHitDirection::Right;
		}
	}

	return EHitDirection::Front;
}

FName URA_BlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Front:
		return FName("Front");
	case EHitDirection::Back:
		return FName("Back");
	case EHitDirection::Left:
		return FName("Left");
	case EHitDirection::Right:
		return FName("Right");
	default:
		return FName("None");
	}
}
