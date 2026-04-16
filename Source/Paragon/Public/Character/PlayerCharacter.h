#pragma once

#include "CoreMinimal.h"
#include "Character/ParagonCharacterBase.h"
#include "InputActionValue.h"
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
	void Look(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC_PlayerCharacter;
};
