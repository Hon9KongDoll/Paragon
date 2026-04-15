#include "Character/ParagonCharacterBase.h"

AParagonCharacterBase::AParagonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}