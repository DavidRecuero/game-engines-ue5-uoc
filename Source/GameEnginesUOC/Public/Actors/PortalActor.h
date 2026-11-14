#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

// Portal with an animated material that teleports any character touching it to a destination in the level
UCLASS()
class GAMEENGINESUOC_API APortalActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalActor();

protected:
	// Trigger volume: only pawns generate overlap events
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	UBoxComponent* BoxComponent;

	// Visual only, shows the animated portal material
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	UStaticMeshComponent* PortalMeshComponent;

	// Any actor placed in the level (e.g. a Target Point) marking where the character appears
	UPROPERTY(EditAnywhere, Category = "Settings")
	AActor* TeleportDestination = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
