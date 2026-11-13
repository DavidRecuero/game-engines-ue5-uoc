#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushCharacterActor.generated.h"

class UBoxComponent;

// Trigger box that pushes back any character trying to get in
UCLASS()
class GAMEENGINESUOC_API APushCharacterActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushCharacterActor();

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ForceImpulse = 10000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
