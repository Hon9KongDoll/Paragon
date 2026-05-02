#include "AbilitySystem/GameplayAbility/ComboGameplayAbility.h"
#include "ParagonGameplayTag.h"

//Engine
#include "GameplayTagsManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
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
		AbilityTask_WaitGameplayEvent->EventReceived.AddDynamic(this, &ThisClass::HandleComboChange);
		AbilityTask_WaitGameplayEvent->ReadyForActivation();
	}

	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* AbilityTask_WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, FGameplayTag::RequestGameplayTag("GameplayEvent.HitDetection"), nullptr, false, true);
		AbilityTask_WaitGameplayEvent->EventReceived.AddDynamic(this, &ThisClass::HandleHitDetectionAndDamage);
		AbilityTask_WaitGameplayEvent->ReadyForActivation();
	}

	SetupAbilityTaskWaitInputPress();
}

void UComboGameplayAbility::HandleComboChange(FGameplayEventData Payload)
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

void UComboGameplayAbility::HandleHitDetectionAndDamage(FGameplayEventData Payload)
{
	if (!K2_HasAuthority()) return;

	const FGameplayAbilityTargetDataHandle& TargetDataHandle = Payload.TargetData;

	TArray<FHitResult> OutHitResult;

	for (const TSharedPtr<FGameplayAbilityTargetData> TargetData : TargetDataHandle.Data)
	{
		FVector StartLocation = TargetData->GetOrigin().GetTranslation();
		FVector EndLocation = TargetData->GetEndPoint();

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

		UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLocation, EndLocation, 30.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHitResult, true);
	}
}

void UComboGameplayAbility::SetupAbilityTaskWaitInputPress()
{
	UAbilityTask_WaitInputPress* AbilityTaskWaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	AbilityTaskWaitInputPress->OnPress.AddDynamic(this, &ThisClass::HandleAbilityTaskWaitInputPress);
	AbilityTaskWaitInputPress->ReadyForActivation();
}

void UComboGameplayAbility::HandleAbilityTaskWaitInputPress(float TimeWaited)
{
	SetupAbilityTaskWaitInputPress();

	if (NextComboName == NAME_None) return;

	if (UAnimInstance* AnimInstance = GetOwnerAnimInstance())
	{	
		AnimInstance->Montage_SetNextSection(AnimInstance->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
	}
}