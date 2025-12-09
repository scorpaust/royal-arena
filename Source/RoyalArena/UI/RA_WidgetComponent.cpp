// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_WidgetComponent.h"
#include "RoyalArena/Characters/RA_BaseCharacter.h"
#include "RoyalArena/AbilitySystem/RA_AbilitySystemComponent.h"
#include "RoyalArena/AbilitySystem/RA_AttributeSet.h"
#include "RoyalArena/UI/RA_AttributeWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "RA_WidgetComponent.h"

void URA_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();

	if (!IsASCInitialized()) 
	{
		RoyalCharacter->OnASCInitialized.AddDynamic(this, &URA_WidgetComponent::OnASCInitialized);
	}

	InitializeAttributeDelegate();
}

void URA_WidgetComponent::InitAbilitySystemData()
{
	RoyalCharacter = Cast<ARA_BaseCharacter>(GetOwner());

	AttributeSet = TWeakObjectPtr<URA_AttributeSet>(Cast<URA_AttributeSet>(RoyalCharacter->GetAttributeSet()));

	AbilitySystemComponent = Cast<URA_AbilitySystemComponent>(RoyalCharacter->GetAbilitySystemComponent());
}

bool URA_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void URA_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<URA_AbilitySystemComponent>(ASC);
	
	AttributeSet = TWeakObjectPtr<URA_AttributeSet>(Cast<URA_AttributeSet>(RoyalCharacter->GetAttributeSet()));

	if (!IsASCInitialized()) return;

	InitializeAttributeDelegate();
}

void URA_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair);

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget) -> void {
			BindWidgetToAttributeChanges(ChildWidget, Pair);
			});
	}
}


void URA_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet.IsValid())
	{
		UE_LOG(LogTemp, Error,
			TEXT("URA_WidgetComponent::InitializeAttributeDelegate - AttributeSet inválido (NULL ou PendingKill)"));
		return;
	}

	URA_AttributeSet* AS = AttributeSet.Get();
	if (!AS)
	{
		UE_LOG(LogTemp, Error,
			TEXT("URA_WidgetComponent::InitializeAttributeDelegate - AttributeSet.Get() retornou nullptr"));
		return;
	}

	if (!AS->bAttributesInitialized)
	{
		AS->OnAttributesInitialized.AddDynamic(this, &URA_WidgetComponent::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}


void URA_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair)
{
	URA_AttributeWidget* AttributeWidget = Cast<URA_AttributeWidget>(WidgetObject);

	if (!IsValid(AttributeWidget)) return;

	if (!AttributeWidget->MatchesAttributes(Pair)) return;

	AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get());

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData) {
		AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get());
		});
}
