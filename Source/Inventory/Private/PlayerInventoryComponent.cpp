// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryComponent.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(InteractionWidgetClass)) {
		UE_LOG(LogTemp, Error, TEXT("InteractionWidgetClass Not Found"));
		return;
	};

	InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	if(!IsValid(InteractionWidget)) {
		UE_LOG(LogTemp, Error, TEXT("InteractionWidget Not Found"));
		return;
	};

	InteractionWidget->AddToViewport();
	// ...

	if (IsValid(InventoryWidgetClass)) {
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);

		InventoryWidget->AddToViewport();

		InventoryWidget->Init(Cols, Rows, InventorySlotWidgetClass);
	}
}

void UPlayerInventoryComponent::SetCurrentLootingObject(APickableObject* LootingObject)
{
	if (LootingObject == CurrentLootingObject) return;

	CurrentLootingObject = LootingObject;

	if(LootingObject == nullptr) {
		InteractionWidget->OnInteractionEnded();
		return;
	};

	InteractionWidget->OnInteractionStarted();
}

// Called every frame
void UPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckLooting(); 

	// ...
}

void UPlayerInventoryComponent::CheckLooting()
{
	if (!bIsCanLoot) return;

	UWorld* World = GetWorld();
	if (!World) {
		SetCurrentLootingObject(nullptr);
		return;
	};;

	AActor* Actor = GetOwner();
	if (!IsValid(Actor)) {
		SetCurrentLootingObject(nullptr);
		return;
	};;

	ACharacter* Character = Cast<ACharacter>(Actor);
	if (!IsValid(Character)) {
		SetCurrentLootingObject(nullptr);
		return;
	};;

	APlayerController* PC = Cast<APlayerController>(Character->GetController());
	if (!IsValid(PC)) {
		SetCurrentLootingObject(nullptr);
		return;
	};

	FVector CamLoc = PC->PlayerCameraManager->GetCameraLocation();
	FRotator CamRot = PC->PlayerCameraManager->GetCameraRotation();

	FVector Start = CamLoc + CamRot.Vector();
	FVector End = CamLoc + CamRot.Vector() * 200.0f;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Actor);

	//DrawDebugLine(World, Start, End, FColor::Red, false, .1f, 0, .1f);

	if (bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams)) {
		AActor* HitActor = HitResult.GetActor();
		if (!IsValid(HitActor)) {
			SetCurrentLootingObject(nullptr);
			return;
		};

		APickableObject* PickableObject = Cast<APickableObject>(HitActor);
		if (!IsValid(PickableObject)) {
			SetCurrentLootingObject(nullptr);
			return;
		};

		bool bIsLootable = PickableObject->CanBePickedUp();
		if (!bIsLootable) {
			SetCurrentLootingObject(nullptr);
			return;
		};

		SetCurrentLootingObject(PickableObject);
		return;
	}

	SetCurrentLootingObject(nullptr);
}

void UPlayerInventoryComponent::SetCanLoot(bool bCanLoot)
{
	bIsCanLoot = bCanLoot;
}

void UPlayerInventoryComponent::PickUp()
{
	if (!IsValid(CurrentLootingObject)) return;

	CurrentLootingObject->PickUp();
	SetCurrentLootingObject(nullptr);
}

void UPlayerInventoryComponent::Open(){

}

void UPlayerInventoryComponent::Close() {}