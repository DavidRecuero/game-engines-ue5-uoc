#include "Actors/PortalActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

// Sets default values
APortalActor::APortalActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Ignore everything except pawns, which only generate overlap events
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PortalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PortalMeshComponent");
	PortalMeshComponent->SetupAttachment(RootComponent);
	PortalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APortalActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APortalActor::BeginOverlap);
}

void APortalActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!IsValid(Character)) return;

	if (!IsValid(TeleportDestination))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Portal has no TeleportDestination assigned"));
		}
		return;
	}

	// TeleportTo moves the character safely, keeping its current rotation
	Character->TeleportTo(TeleportDestination->GetActorLocation(), Character->GetActorRotation());
}
