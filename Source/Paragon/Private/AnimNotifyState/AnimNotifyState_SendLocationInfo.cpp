#include "AnimNotifyState/AnimNotifyState_SendLocationInfo.h"

//Engine
#include "AbilitySystemBlueprintLibrary.h"

void UAnimNotifyState_SendLocationInfo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	SocketLocations.Empty();

	AddSocketLocations(MeshComp);
}

void UAnimNotifyState_SendLocationInfo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AddSocketLocations(MeshComp);
}

void UAnimNotifyState_SendLocationInfo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	AddSocketLocations(MeshComp);

	if (!MeshComp->GetOwner()) return;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());

	if (!ASC) return;

	FGameplayEventData EventData;

	for (int i = 1; i < SocketLocations.Num(); ++i)
	{
		FVector StartLocation = SocketLocations[i - 1];
		FVector EndLocation = SocketLocations[i];

		// Construct TargetData
		FGameplayAbilityTargetData_LocationInfo* NewData = new FGameplayAbilityTargetData_LocationInfo();
		NewData->SourceLocation.LiteralTransform.SetLocation(StartLocation);
		NewData->TargetLocation.LiteralTransform.SetLocation(EndLocation);
		EventData.TargetData.Add(NewData);
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, EventData);
}

void UAnimNotifyState_SendLocationInfo::AddSocketLocations(USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp) return;

	if (MeshComp->DoesSocketExist(SocketName))
	{
		FVector Location = MeshComp->GetSocketLocation(SocketName);

		SocketLocations.Add(Location);
	}
}
