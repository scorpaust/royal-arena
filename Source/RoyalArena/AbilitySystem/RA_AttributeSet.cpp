// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_AttributeSet.h"
#include "Net/UnrealNetwork.h"

void URA_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URA_AttributeSet, Health, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URA_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URA_AttributeSet, Mana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URA_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME(URA_AttributeSet, bAttributesInitialized);
}

void URA_AttributeSet::PostGameplayEffectExecute( const FGameplayEffectModCallbackData& Data) 
{
	Super::PostGameplayEffectExecute(Data);

	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;

		OnAttributesInitialized.Broadcast();
	}
}

void URA_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URA_AttributeSet, Health, OldValue);
}

void URA_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URA_AttributeSet, MaxHealth, OldValue);
}

void URA_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URA_AttributeSet, Mana, OldValue);
}

void URA_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URA_AttributeSet, MaxMana, OldValue);
}

void URA_AttributeSet::OnRep_AttributesInitialized()
{
	if (bAttributesInitialized)
	{
		OnAttributesInitialized.Broadcast();
	}
}
