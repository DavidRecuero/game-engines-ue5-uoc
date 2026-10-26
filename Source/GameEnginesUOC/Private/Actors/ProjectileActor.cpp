#include "Actors/ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// The collision sphere is the root, so the movement component sweeps with it
	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>("ProjectileCollisionComponent");
	SetRootComponent(ProjectileCollisionComponent);
	ProjectileCollisionComponent->InitSphereRadius(8.0f);
	ProjectileCollisionComponent->SetCollisionProfileName("BlockAll");
	ProjectileCollisionComponent->SetNotifyRigidBodyCollision(true);

	// The mesh is only visual
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMeshComponent");
	ProjectileMeshComponent->SetupAttachment(RootComponent);
	ProjectileMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = 750.0f;
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	// Don't collide with the character that fired it
	if (GetOwner())
	{
		ProjectileCollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	}

	ProjectileCollisionComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileActor::OnProjectileHit);
	SetLifeSpan(10.0f);
}

void AProjectileActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ProjectileCollisionComponent->OnComponentHit.RemoveAll(this);
}

void AProjectileActor::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}