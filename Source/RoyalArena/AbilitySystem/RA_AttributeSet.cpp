// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h" // Add this include at the top of the file
#include "AbilitySystemBlueprintLibrary.h"
#include "../GameplayTags/RATags.h"

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

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() <= 0.f)
	{
		FGameplayEventData Payload;

		Payload.Instigator = Data.Target.GetAvatarActor();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Data.EffectSpec.GetEffectContext().GetInstigator(),
			RATags::Events::KillScored,
			Payload);
	}


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
