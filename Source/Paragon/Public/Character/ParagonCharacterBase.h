#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ParagonCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class PARAGON_API AParagonCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AParagonCharacterBase();

	//{@ Ability System

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY();
	TObjectPtr<UAttributeSet> AttributeSet;

	//@}
};