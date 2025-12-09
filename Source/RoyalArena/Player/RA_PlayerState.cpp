// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_PlayerState.h"
#include "../AbilitySystem/RA_AttributeSet.h"
#include "../AbilitySystem/RA_AbilitySystemComponent.h"

ARA_PlayerState::ARA_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<URA_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URA_AttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ARA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
