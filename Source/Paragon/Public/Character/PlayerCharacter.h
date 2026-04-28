#pragma once

#include "CoreMinimal.h"
#include "Character/ParagonCharacterBase.h"
#include "InputActionValue.h"
#include "ParagonEnum.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class PARAGON_API APlayerCharacter : public AParagonCharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void PawnClientRestart() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector GetLookForwardDirection();

	FVector GetLookRightDirection();

	FVector GetMoveForwardDirection();

	//{@ Input Action

	void Look(const FInputActionValue& InputActionValue);

	void Move(const FInputActionValue& InputActionValue);

	void HandleGameplayAbilityInput(const FInputActionValue& InputActionValue, EGameplayAbilityInputID GameplayAbilityInputID);

private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly)
	TMap<EGameplayAbilityInputID, TObjectPtr<UInputAction>> GameplayAbilityInputActions;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC_PlayerCharacter;

	//@}

private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;
};
