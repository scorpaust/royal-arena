// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_EnemyCharacter.h"
#include "../AbilitySystem/RA_AttributeSet.h"
#include "../AbilitySystem/RA_AbilitySystemComponent.h"

ARA_EnemyCharacter::ARA_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<URA_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URA_AttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ARA_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ARA_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ARA_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (!HasAuthority()) return;

	InitializeAttributes();

	GiveStartupAbilities();

	URA_AttributeSet* RAAttributeSet = Cast<URA_AttributeSet>(GetAttributeSet());

	if (!IsValid(RAAttributeSet)) return;

	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
		RAAttributeSet->GetHealthAttribute()
	).AddUObject(this, &ARA_EnemyCharacter::OnHealthChanged);
}
