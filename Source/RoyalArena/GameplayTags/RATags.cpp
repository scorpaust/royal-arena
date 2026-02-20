// Dinis Miguel Costa - Todos os direitos reservados


#include "RATags.h"

namespace RATags
{
	namespace RAAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "RATags.RAAbilities.ActivateOnGiven", "Tag for abilities that should activate immediately once given")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "RATags.RAAbilities.Primary", "Tag for the Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "RATags.RAAbilities.Secondary", "Tag for the Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "RATags.RAAbilities.Tertiary", "Tag for the Tertiary Ability")
	}

	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "RATags.Events.KillScored", "Tag for the KillScored event.")
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "RATags.Events.Enemy.HitReact", "Tag for enemy hit react event")
		}
	}
}

