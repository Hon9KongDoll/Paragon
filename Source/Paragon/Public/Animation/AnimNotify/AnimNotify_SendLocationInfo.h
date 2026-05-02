#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_SendLocationInfo.generated.h"

UCLASS()
class PARAGON_API UAnimNotify_SendLocationInfo : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<FName> TargetSocketNames;

	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
};
