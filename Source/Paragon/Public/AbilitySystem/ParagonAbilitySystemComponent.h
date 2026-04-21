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

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;
};
