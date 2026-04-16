#include "Character/PlayerCharacter.h"

//Engine
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
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
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);
	}
}

void APlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(-Value.Y);
	AddControllerYawInput(Value.X);
}
