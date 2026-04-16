#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ParagonAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class PARAGON_API UParagonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, meta =(BlueprintThreadSafe))
	FORCEINLINE float GetMoveSpeed() const { return MoveSpeed; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsMoving() const { return MoveSpeed != 0.f; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsNotMoving() const { return MoveSpeed == 0.f; }

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerCharacterMovement;

	UPROPERTY()
	float MoveSpeed;
};
