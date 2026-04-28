#include "AbilitySystem/GameplayAbility/ComboGameplayAbility.h"

//Engine
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UComboGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!K2_CommitAbility())
	{
		K2_EndAbility();

		return;
	}

	// 判断当前上下文是否具有“服务器权威”或“有效的预测权限”
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* AbilityTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		AbilityTask->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask->OnCancelled.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask->ReadyForActivation();
	}
}
