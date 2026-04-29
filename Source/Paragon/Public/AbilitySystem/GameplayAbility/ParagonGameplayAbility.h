#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ParagonGameplayAbility.generated.h"

UCLASS()
class PARAGON_API UParagonGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UAnimInstance* GetOwnerAnimInstance() const;
};
