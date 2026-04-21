#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ParagonAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PARAGON_API UParagonAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UParagonAttributeSet, Health)

	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UParagonAttributeSet, MaxHealth)

	UPROPERTY()
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UParagonAttributeSet, Mana)

	UPROPERTY()
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UParagonAttributeSet, MaxMana)
};
