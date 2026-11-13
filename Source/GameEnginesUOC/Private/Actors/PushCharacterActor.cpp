#include "Actors/PushCharacterActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

// Sets default values
APushCharacterActor::APushCharacterActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	// Ignore everything except pawns, which only generate overlap events
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void APushCharacterActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APushCharacterActor::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &APushCharacterActor::EndOverlap);
}

void APushCharacterActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("A PAWN HAS ENTERED"));
	}

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!IsValid(Character)) return;

	// Launch the character backwards, keeping its current vertical velocity
	Character->LaunchCharacter(-OtherActor->GetActorForwardVector() * ForceImpulse, true, false);
}

void APushCharacterActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("A PAWN HAS LEFT"));
	}
}
