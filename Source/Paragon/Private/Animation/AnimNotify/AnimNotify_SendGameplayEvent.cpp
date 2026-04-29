#include "Animation/AnimNotify/AnimNotify_SendGameplayEvent.h"

//Engine
#include "GameplayTagsManager.h"
#include "AbilitySystemBlueprintLibrary.h"

FString UAnimNotify_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (EventTag.IsValid())
	{
		TArray<FName> OutNames;

		UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, OutNames);

		return OutNames.Last().ToString();
	}

	return FString();
}

void UAnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp->GetOwner()) return;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());

	if (!ASC) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}
