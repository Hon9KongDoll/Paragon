#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/ParagonGameplayAbility.h"
#include "ComboGameplayAbility.generated.h"

UCLASS()
class PARAGON_API UComboGameplayAbility : public UParagonGameplayAbility
{
	GENERATED_BODY()
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

};
