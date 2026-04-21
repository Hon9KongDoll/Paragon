#include "PlayerController/ParagonPlayerController.h"
#include "Character/ParagonCharacterBase.h"

void AParagonPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (AParagonCharacterBase* ParagonCharacterBase = Cast<AParagonCharacterBase>(P))
	{
		ParagonCharacterBase->ClientSideInitializationASC();
	}
}

void AParagonPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (AParagonCharacterBase* ParagonCharacterBase = Cast<AParagonCharacterBase>(aPawn))
	{
		ParagonCharacterBase->ServerSideInitializationASC();
	}
}
