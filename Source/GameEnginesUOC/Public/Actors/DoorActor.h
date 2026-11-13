#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactuable.h"
#include "DoorActor.generated.h"

// Door that toggles between open and closed when the player interacts with it
UCLASS()
class GAMEENGINESUOC_API ADoorActor : public AActor, public IInteractuable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorActor();

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	// Offset applied to the door location when it opens/closes (must be non-zero, e.g. Z = -250)
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector DoorMovementOffset;

	bool bIsDoorOpen = false;

	void OpenCloseDoor();
};
