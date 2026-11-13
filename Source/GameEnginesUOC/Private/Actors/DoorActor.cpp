#include "Actors/DoorActor.h"

// Sets default values
ADoorActor::ADoorActor()
{
	// The door only changes when interacted with, no need to tick
	PrimaryActorTick.bCanEverTick = false;
}

void ADoorActor::Interact_Implementation(AActor* Interactor)
{
	bIsDoorOpen = !bIsDoorOpen;
	OpenCloseDoor();
}

void ADoorActor::OpenCloseDoor()
{
	// Opening moves the door by -Offset, closing moves it back by +Offset
	const FVector DoorLocation = GetActorLocation() + DoorMovementOffset * ((bIsDoorOpen) ? -1 : 1);
	SetActorLocation(DoorLocation);
}
