#include "Character/ParagonCharacterBase.h"
#include "AbilitySystem/ParagonAttributeSet.h"
#include "AbilitySystem/ParagonAbilitySystemComponent.h"

AParagonCharacterBase::AParagonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AbilitySystemComponent = CreateDefaultSubobject<UParagonAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UParagonAttributeSet>("AttributeSet");
}