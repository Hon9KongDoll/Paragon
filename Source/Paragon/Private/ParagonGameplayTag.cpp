#include "ParagonGameplayTag.h"

namespace PargonGameplayAbilityTag
{
	UE_DEFINE_GAMEPLAY_TAG(Ability_BasicAttack, FName(TEXTVIEW("Ability.BasicAttack")))
}

namespace PargonGameplayEventTag
{
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_ComboChange_End, FName(TEXTVIEW("GameplayEvent.ComboChange.End")))
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_ComboChange_Combo01, FName(TEXTVIEW("GameplayEvent.ComboChange.Combo01")))
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_ComboChange_Combo02, FName(TEXTVIEW("GameplayEvent.ComboChange.Combo02")))
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_ComboChange_Combo03, FName(TEXTVIEW("GameplayEvent.ComboChange.Combo03")))
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_ComboChange_Combo04, FName(TEXTVIEW("GameplayEvent.ComboChange.Combo04")))
}