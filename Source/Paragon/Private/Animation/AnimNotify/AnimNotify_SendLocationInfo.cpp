#include "Animation/AnimNotify/AnimNotify_SendLocationInfo.h"

//Engine
#include "AbilitySystemBlueprintLibrary.h"

void UAnimNotify_SendLocationInfo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	if (!MeshComp->GetOwner()) return;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());

	if (!ASC) return;

	FGameplayEventData EventData;

	for (int i = 1; i < TargetSocketNames.Num(); ++i)
	{
		FVector StartLocation = MeshComp->GetSocketLocation(TargetSocketNames[i - 1]);
		FVector EndLocation = MeshComp->GetSocketLocation(TargetSocketNames[i]);

		// Construct TargetData
		FGameplayAbilityTargetData_LocationInfo* NewData = new FGameplayAbilityTargetData_LocationInfo();
		NewData->SourceLocation.LiteralTransform.SetLocation(StartLocation);
		NewData->TargetLocation.LiteralTransform.SetLocation(EndLocation);
		EventData.TargetData.Add(NewData);
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, EventData);
}
