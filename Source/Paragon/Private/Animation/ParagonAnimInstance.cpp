#include "Animation/ParagonAnimInstance.h"

//Engine
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	if (OwnerCharacter && OwnerCharacterMovement)
	{
		MoveSpeed = OwnerCharacterMovement->Velocity.Length();

		FRotator BodyRotation = OwnerCharacter->GetActorRotation();

		// 处理角度转变，计算旋转差值
		FRotator BodyDeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(BodyRotation, BodyPreviousRotation);

		BodyPreviousRotation = BodyRotation;

		if (DeltaSeconds > KINDA_SMALL_NUMBER)
		{
			YawSpeed = BodyDeltaRotation.Yaw / DeltaSeconds;

			SmoothedYawSpeed = FMath::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, SmoothedYawSpeedInterpSpeed);
		}

		bIsJumping = OwnerCharacterMovement->IsFalling();

		// 计算头部转向偏移
		FRotator ControllerRotation = OwnerCharacter->GetBaseAimRotation();
		LookRotationAimOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControllerRotation, BodyRotation);
	}
}

void UParagonAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
