#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ParagonAttributeSet.h"
#include "AbilitySystem/ParagonAbilitySystemComponent.h"
#include "ParagonCharacterBase.generated.h"

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

	void ClientSideInitializationASC();
	void ServerSideInitializationASC();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	TObjectPtr<UParagonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY();
	TObjectPtr<UParagonAttributeSet> AttributeSet;

	//@}
};