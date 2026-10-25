#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class GAMEENGINESUOC_API UMyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsMoving = false;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float Velocity = 0.0f;

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};