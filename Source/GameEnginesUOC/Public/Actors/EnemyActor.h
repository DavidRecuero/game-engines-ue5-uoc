#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

class UStaticMeshComponent;
class UHealthComponent;

// Static enemy (a cube mesh) that takes damage from the player's shots and disappears when its health runs out
UCLASS()
class GAMEENGINESUOC_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	UHealthComponent* HealthComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthDepleted();
};
