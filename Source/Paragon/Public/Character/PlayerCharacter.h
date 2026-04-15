#pragma once

#include "CoreMinimal.h"
#include "Character/ParagonCharacterBase.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PARAGON_API APlayerCharacter : public AParagonCharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;
};
