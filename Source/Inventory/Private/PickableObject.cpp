// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableObject.h"

// Sets default values
APickableObject::APickableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	RootComponent = MeshComponent;
}

bool APickableObject::CanBePickedUp_Implementation() const
{
	return true;
}

void APickableObject::PickUp_Implementation()
{
	Destroy();
}

// Called when the game starts or when spawned
void APickableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void APickableObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APickableObject, Mesh))
	{
		if (!IsValid(Mesh) || !IsValid(MeshComponent)) return;

		MeshComponent->SetStaticMesh(Mesh);
	}
}
#endif