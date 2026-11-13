#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactuable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractuable : public UInterface
{
	GENERATED_BODY()
};

// Contract for any actor the player can interact with (doors, buttons, items...)
class GAMEENGINESUOC_API IInteractuable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AActor* Interactor);
};
