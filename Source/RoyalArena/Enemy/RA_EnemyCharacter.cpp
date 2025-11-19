// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_EnemyCharacter.h"
#include "../AbilitySystem/RA_AbilitySystemComponent.h"

ARA_EnemyCharacter::ARA_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<URA_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* ARA_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARA_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	if (!HasAuthority()) return;

	GiveStartupAbilities();
}
