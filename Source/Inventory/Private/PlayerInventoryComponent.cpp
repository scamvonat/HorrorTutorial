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
		InventoryWidget->OnInventoryClose.AddDynamic(this, &UPlayerInventoryComponent::Close);

		InventoryWidget->OnMouseEnterSlot.AddDynamic(this, &UPlayerInventoryComponent::OnMouseEnterSlot);
		InventoryWidget->OnMouseLeaveSlot.AddDynamic(this, &UPlayerInventoryComponent::OnMouseLeaveSlot);
		Close();
	}

	AActor* Actor = GetOwner();
	if (!IsValid(Actor)) {
		UE_LOG(LogTemp, Error, TEXT("Owner Not Found"));
		return;
	};

	InventoryComponent = Actor->GetComponentByClass<UInventoryComponent>();

	if(!IsValid(InventoryComponent)) {
		UE_LOG(LogTemp, Error, TEXT("InventoryComponent Not Found"));
		return;
	};

	InventoryComponent->OnAddItem.AddDynamic(this, &UPlayerInventoryComponent::OnAddItem);
	InventoryComponent->OnRemoveItem.AddDynamic(this, &UPlayerInventoryComponent::OnRemoveItem);
}

void UPlayerInventoryComponent::OnAddItem(FInventoryAddEvent EventData)
{
	UDAItem* ItemData = UItemUtils::GetItemByID(EventData.AddedItem.ItemName);
	int32 NewQuantity = EventData.AddedItem.Quantity + EventData.Slot.Quantity;
	
	InventoryWidget->UpdateSlot(
		EventData.SlotIndex,
		ItemData->ItemIcon,
		NewQuantity
		);
}

void UPlayerInventoryComponent::OnRemoveItem(FInventoryRemoveEvent EventData)
{
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

void UPlayerInventoryComponent::OnMouseEnterSlot(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("SLOT %s"), *FString::FromInt(Index));
	
	TArray<FItemStruct> Items = InventoryComponent->GetInventoryItems();
	if (!Items.IsValidIndex(Index)) return;

	FItemStruct& Item = Items[Index];
	if (Item.ItemName.IsNone()) return;
	
	UDAItem* ItemData = UItemUtils::GetItemByID(Item.ItemName);

	if (!IsValid(ItemData)) return;
	InventoryWidget->SetSlotTooltip(ItemData->ItemName, ItemData->ItemDescription, ItemData->ItemIcon);
	
	InventoryWidget->SetSlotTooltipVisibility(ESlateVisibility::Visible);
}

void UPlayerInventoryComponent::OnMouseLeaveSlot(int32 Index)
{
	InventoryWidget->SetSlotTooltipVisibility(ESlateVisibility::Hidden);
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

	FItemStruct ItemData = CurrentLootingObject->GetItem();

	InventoryComponent->AddItem(ItemData);
	
	CurrentLootingObject->PickUp();
	SetCurrentLootingObject(nullptr);
}

void UPlayerInventoryComponent::Open(){
	UE_LOG(LogTemp, Display, TEXT("Open"));
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	bIsOpen = true;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PC))
	{
		SetCurrentLootingObject(nullptr);
		UE_LOG(LogTemp, Error, TEXT("PlayerController Not Found"));
		return;
	}
	
	PC->SetShowMouseCursor(true);

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PC->SetInputMode(InputMode);
}

void UPlayerInventoryComponent::Close()
{
	UE_LOG(LogTemp, Display, TEXT("Close"));
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	bIsOpen = false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PC))
	{
		SetCurrentLootingObject(nullptr);
		UE_LOG(LogTemp, Error, TEXT("PlayerController Not Found"));
		return;
	}

	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());
}

// void UPlayerInventoryComponent::Toggle()
// {
// 	UE_LOG(LogTemp, Display, TEXT("Toggle"));
// 	
// 	bIsOpen ? Close() : Open();
// }
