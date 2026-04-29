#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/ParagonGameplayAbility.h"
#include "ComboGameplayAbility.generated.h"

UCLASS()
class PARAGON_API UComboGameplayAbility : public UParagonGameplayAbility
{
	GENERATED_BODY()
	
public:
	UComboGameplayAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void HandleWaitGameplayEvent(FGameplayEventData Payload);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> ComboMontage;

	FName NextComboName;
};
