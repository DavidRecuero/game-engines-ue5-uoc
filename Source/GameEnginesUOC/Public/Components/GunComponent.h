#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GunComponent.generated.h"

// Visual weapon mesh that also owns the hitscan (line trace) firing logic
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEENGINESUOC_API UGunComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UGunComponent();

	// Traces a straight line forward from the given fire point
	void Fire(USceneComponent* FirePosComponent);

protected:
	// Maximum range of the shot
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float Distance = 1000.0f;
};
