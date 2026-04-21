#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ParagonPlayerController.generated.h"

UCLASS()
class PARAGON_API AParagonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 仅在客户端调用
	virtual void AcknowledgePossession(class APawn* P) override;

protected:
	// 仅在服务器端调用
	virtual void OnPossess(APawn* aPawn) override;
};
