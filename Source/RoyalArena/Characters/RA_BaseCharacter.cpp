// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"

namespace RoyalTags
{
	const FName Player = FName("Player");
}

ARA_BaseCharacter::ARA_BaseCharacter()
{
 
	PrimaryActorTick.bCanEverTick = false;

	// Tick and refresh bones even when not rendered for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

}

UAbilitySystemComponent* ARA_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ARA_BaseCharacter::GiveStartupAbilities()
{
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);

		if (Ability)
		{
			UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

			if (!IsValid(ASC)) return;

			ASC->GiveAbility(AbilitySpec);	
		}
	}	
}

void ARA_BaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect is not valid on %s. Please set the GameplayEffect used to initialize attributes in the Character Blueprint."), *GetName());

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();

	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1, ContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ARA_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f && IsAlive())
	{
		HandleDeath();
	}
}

void ARA_BaseCharacter::HandleDeath()
{
	bAlive = false;
}

void ARA_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARA_BaseCharacter, bAlive);
}

void ARA_BaseCharacter::HandleRespawn()
{
	bAlive = true;
}

void ARA_BaseCharacter::ResetAttributes()
{
	if (IsValid(GetAbilitySystemComponent()) && IsValid(ResetAttributesEffect))
	{
		FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
		
		FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(ResetAttributesEffect, 1.f, ContextHandle);
		
		if (SpecHandle.IsValid() && SpecHandle.Data.IsValid())
		{
			GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}

	}
}

