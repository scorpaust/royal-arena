// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_AbilitySystemComponent.h"
#include "../GameplayTags/RATags.h"

void URA_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	// You can add custom logic here when an ability is given

	HandleAutoActivatedAbility(AbilitySpec);
}

void URA_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	// You can add custom logic here when abilities are activated on clients

	FScopedAbilityListLock ActiveScopeLock(*this);

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(AbilitySpec);
	}
}

void URA_AbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 NewLevel)
{
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;

	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);

	if (AbilitySpec)
	{
		AbilitySpec->Level = NewLevel;

		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void URA_AbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 LevelToAdd)
{
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;

	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);

	if (AbilitySpec)
	{
		AbilitySpec->Level += LevelToAdd;

		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void URA_AbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!AbilitySpec.Ability) return; // Ensure the ability is valid

	for (const FGameplayTag& Tag : AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(RATags::RAAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);

			return;
		}
	}
}
