#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ParagonAbilitySystemComponent.generated.h"

UCLASS()
class PARAGON_API UParagonAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void ApplyDefaultGameplayEffectToSelf();

	void GiveDefaultGameplayAbilityToSelf();

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> DefaultGameplayAbilities;
};
