#include "Character/PlayerCharacter.h"

//Engine
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

void APlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if (!EnhancedInputLocalPlayerSubsystem->HasMappingContext(IMC_PlayerCharacter))
		{
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(IMC_PlayerCharacter, 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::PawnClientRestart - PlayerController is nullptr."));
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);

		for (const TPair<EGameplayAbilityInputID, TObjectPtr<UInputAction>>& Pair : GameplayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(Pair.Value, ETriggerEvent::Triggered, this, &ThisClass::HandleGameplayAbilityInput, Pair.Key);
		}
	}
}

FVector APlayerCharacter::GetLookForwardDirection()
{
	return Camera->GetForwardVector();
}

FVector APlayerCharacter::GetLookRightDirection()
{
	return Camera->GetRightVector();
}

FVector APlayerCharacter::GetMoveForwardDirection()
{
	// CrossProduct 向量叉乘：两个向量做叉乘，得到一个同时垂直于它们的新向量
	return FVector::CrossProduct(GetLookRightDirection(), FVector::UpVector);
}

void APlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(-Value.Y);
	AddControllerYawInput(Value.X);
}

void APlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D Value = InputActionValue.Get<FVector2D>();

	// 不 Normalize 的问题：Value = (1, 1) 斜向移动，长度是 √2 ≈ 1.41，斜着走比直走更快
	// Normalize 后：右上 (0.7,0.7)，长度统一，移动速度一致
	Value.Normalize();

	AddMovementInput(Value.Y * GetMoveForwardDirection() + Value.X * GetLookRightDirection());
}

void APlayerCharacter::HandleGameplayAbilityInput(const FInputActionValue& InputActionValue, EGameplayAbilityInputID GameplayAbilityInputID)
{
	bool bPressed = InputActionValue.Get<bool>();

	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)GameplayAbilityInputID);
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)GameplayAbilityInputID);
	}
}
