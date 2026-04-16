#include "Animation/ParagonAnimInstance.h"

//Engine
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UParagonAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

	if (OwnerCharacter)
	{
		OwnerCharacterMovement = OwnerCharacter->GetCharacterMovement();
	}
}

void UParagonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter)
	{
		MoveSpeed = OwnerCharacterMovement->Velocity.Length();
	}
}

void UParagonAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
