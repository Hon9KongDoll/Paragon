#include "AbilitySystem/GameplayAbility/ComboGameplayAbility.h"
#include "ParagonGameplayTag.h"

//Engine
#include "GameplayTagsManager.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UComboGameplayAbility::UComboGameplayAbility()
{
	AbilityTags.AddTag(PargonGameplayAbilityTag::Ability_BasicAttack);
	BlockAbilitiesWithTag.AddTag(PargonGameplayAbilityTag::Ability_BasicAttack);
}

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
		UAbilityTask_PlayMontageAndWait* AbilityTask_PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, ComboMontage);
		AbilityTask_PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask_PlayMontageAndWait->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask_PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask_PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::K2_EndAbility);
		AbilityTask_PlayMontageAndWait->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* AbilityTask_WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, FGameplayTag::RequestGameplayTag("GameplayEvent.ComboChange"), nullptr, false, false);
		AbilityTask_WaitGameplayEvent->EventReceived.AddDynamic(this, &ThisClass::HandleWaitGameplayEvent);
		AbilityTask_WaitGameplayEvent->ReadyForActivation();
	}
}

void UComboGameplayAbility::HandleWaitGameplayEvent(FGameplayEventData Payload)
{
	if (Payload.EventTag == FGameplayTag::RequestGameplayTag("GameplayEvent.ComboChange.End"))
	{
		NextComboName = NAME_None;
		return;
	}

	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(Payload.EventTag, TagNames);
	NextComboName = TagNames.Last();
}
