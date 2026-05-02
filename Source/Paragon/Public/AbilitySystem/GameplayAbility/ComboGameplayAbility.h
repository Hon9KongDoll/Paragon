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
	void HandleComboChange(FGameplayEventData Payload);

	UFUNCTION()
	void HandleHitDetectionAndDamage(FGameplayEventData Payload);

	void SetupAbilityTaskWaitInputPress();

	UFUNCTION()
	void HandleAbilityTaskWaitInputPress(float TimeWaited);

	TSubclassOf<UGameplayEffect> GetDamageGameplayEffectForCurrentCombo();

private:
	FName NextComboName;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> ComboMontage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultComboDamageGE;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TSubclassOf<UGameplayEffect>> ComboDamageGE;
};
