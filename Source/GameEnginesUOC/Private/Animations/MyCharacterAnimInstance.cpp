#include "Animations/MyCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"

void UMyCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Pawn = TryGetPawnOwner();
	if (!IsValid(Pawn)) return;

	CharacterMovementComponent = Pawn->GetComponentByClass<UCharacterMovementComponent>();
}

void UMyCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(CharacterMovementComponent)) return;

	// Horizontal speed drives the Idle/Walk/Run blend space
	const FVector CharacterVelocity = CharacterMovementComponent->Velocity;
	Velocity = CharacterVelocity.Size2D();
	IsMoving = Velocity > 0;
}