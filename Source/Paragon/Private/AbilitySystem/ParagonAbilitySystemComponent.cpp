#include "AbilitySystem/ParagonAbilitySystemComponent.h"

void UParagonAbilitySystemComponent::ApplyDefaultGameplayEffectToSelf()
{
	if (GetOwner()->HasAuthority())
	{
		for (const TSubclassOf<UGameplayEffect>& GameplayEffectClass : DefaultGameplayEffects)
		{
			const FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();

			const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

			ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}
