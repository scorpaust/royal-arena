// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_AttributeWidget.h"

void URA_AttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, URA_AttributeSet* AttributeSet)
{
	const float AttributeValue = Pair.Key.GetNumericValueChecked(AttributeSet);

	const float MaxAttributeValue = Pair.Value.GetNumericValueChecked(AttributeSet);

	BP_OnAttributeChanged(AttributeValue, MaxAttributeValue);
}

bool URA_AttributeWidget::MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
