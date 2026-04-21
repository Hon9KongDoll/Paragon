#include "AbilitySystem/GameplayAbility/ComboGameplayAbility.h"

void UComboGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("ActivateAbility"));
}
