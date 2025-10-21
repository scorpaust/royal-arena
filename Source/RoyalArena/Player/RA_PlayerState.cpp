// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_PlayerState.h"
#include "AbilitySystemComponent.h"

ARA_PlayerState::ARA_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ARA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
