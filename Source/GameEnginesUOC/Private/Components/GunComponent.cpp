#include "Components/GunComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

UGunComponent::UGunComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// The gun is only visual, it must not block anything
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UGunComponent::Fire(USceneComponent* FirePosComponent)
{
	if (!IsValid(FirePosComponent)) return;

	FHitResult OutHit;
	const FVector StartPos = FirePosComponent->GetComponentLocation();
	const FVector EndPos = StartPos + FirePosComponent->GetForwardVector() * Distance;

	// Never hit the character holding the gun
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 1.0f);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartPos, EndPos, ECC_Visibility, CollisionQueryParams))
	{
		if (OutHit.bBlockingHit && IsValid(OutHit.GetActor()) && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("Hitting Actor: %s, Impact Point: %s, Impact Normal: %s"),
				*OutHit.GetActor()->GetName(),
				*OutHit.ImpactPoint.ToString(),
				*OutHit.ImpactNormal.ToString()));
		}

		// Deal damage to whatever was hit; actors with a HealthComponent will react to it
		if (IsValid(OutHit.GetActor()))
		{
			APawn* OwnerPawn = Cast<APawn>(GetOwner());
			AController* InstigatorController = IsValid(OwnerPawn) ? OwnerPawn->GetController() : nullptr;
			UGameplayStatics::ApplyDamage(OutHit.GetActor(), Damage, InstigatorController, GetOwner(), UDamageType::StaticClass());
		}
	}
}
