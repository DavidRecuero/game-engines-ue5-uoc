#include "Actors/EnemyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HealthComponent.h"
#include "Engine/Engine.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// The mesh (a cube, assigned in the BP) is what the line trace hits
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthDepleted.AddUniqueDynamic(this, &AEnemyActor::OnHealthDepleted);
}

void AEnemyActor::OnHealthDepleted()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s destroyed"), *GetName()));
	}

	Destroy();
}
