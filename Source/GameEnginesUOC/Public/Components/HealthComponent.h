#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);

// Reusable health: listens to the damage received by its owner and notifies when it runs out
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEENGINESUOC_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	// Fired once when health drops to zero or below
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthDepleted OnHealthDepleted;

protected:
	UPROPERTY(EditAnywhere, Category = "Settings")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Settings")
	float Health = 0.0f;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
