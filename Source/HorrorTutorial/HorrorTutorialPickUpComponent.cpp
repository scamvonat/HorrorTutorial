// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorTutorialPickUpComponent.h"

UHorrorTutorialPickUpComponent::UHorrorTutorialPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UHorrorTutorialPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UHorrorTutorialPickUpComponent::OnSphereBeginOverlap);
}

void UHorrorTutorialPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AHorrorTutorialCharacter* Character = Cast<AHorrorTutorialCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
