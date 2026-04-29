#include "AbilitySystem/GameplayAbility/ParagonGameplayAbility.h"

UAnimInstance* UParagonGameplayAbility::GetOwnerAnimInstance() const
{
	USkeletalMeshComponent* SkeletalMeshComponent = GetOwningComponentFromActorInfo();

	if (SkeletalMeshComponent)
	{
		return SkeletalMeshComponent->GetAnimInstance();
	}

	return nullptr;
}
