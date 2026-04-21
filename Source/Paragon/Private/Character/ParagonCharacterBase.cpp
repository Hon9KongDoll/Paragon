#include "Character/ParagonCharacterBase.h"

AParagonCharacterBase::AParagonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AbilitySystemComponent = CreateDefaultSubobject<UParagonAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UParagonAttributeSet>("AttributeSet");
}

void AParagonCharacterBase::ClientSideInitializationASC()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AParagonCharacterBase::ServerSideInitializationASC()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	AbilitySystemComponent->ApplyDefaultGameplayEffectToSelf();
}
