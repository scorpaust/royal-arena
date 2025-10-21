// Dinis Miguel Costa - Todos os direitos reservados


#include "RA_BaseCharacter.h"

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

