// Dinis Miguel Costa - Todos os direitos reservados

#include "RA_AttributeChangeTask.h"
#include "AbilitySystemComponent.h"

URA_AttributeChangeTask* URA_AttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	URA_AttributeChangeTask* WaitForAttributeChangeTask = NewObject<URA_AttributeChangeTask>();

	WaitForAttributeChangeTask->ASC = TWeakObjectPtr<UAbilitySystemComponent>(AbilitySystemComponent);
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot();

		return nullptr;
	}	

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &URA_AttributeChangeTask::AttributeChanged);

	return WaitForAttributeChangeTask;
}

void URA_AttributeChangeTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	
	SetReadyToDestroy();	

	MarkAsGarbage();
}

void URA_AttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
