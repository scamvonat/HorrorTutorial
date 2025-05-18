// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

int32 UInventoryComponent::GetColCount() const
{
	return Cols;
}

int32 UInventoryComponent::GetRowCount() const
{
	return Rows;
}

int32 UInventoryComponent::GetSlotCount() const
{
	return Rows * Cols;
}

void UInventoryComponent::AddItem(const FItemStruct& Item)
{
	FDataValidationContext Context;
	
	if (Item.IsDataValid(Context) == EDataValidationResult::Invalid)
	{
		return;
	}

	UDAItem* ItemData = UItemUtils::GetItemByID(Item.ItemName);

	if (!IsValid(ItemData))
	{
		return;
	}

	int32 ItemSlot = GetSlotForItem(Item);
	if (ItemSlot == -1) return;

	if(!InventoryItems.IsValidIndex(ItemSlot)) return;

	FItemStruct& SlotItem = InventoryItems[ItemSlot];

	FInventoryAddEvent AddEvent;

	AddEvent.Slot = SlotItem;
	AddEvent.SlotIndex = ItemSlot;
	AddEvent.AddedItem = Item;

	if (SlotItem.Quantity > 0) {

		SlotItem.Quantity += Item.Quantity;
	}
	else {
		SlotItem = Item;
	}
	
	OnAddItem.Broadcast(AddEvent);
}

int32 UInventoryComponent::GetSlotForItem(const FItemStruct& Item) const
{
	for (int32 Index = 0; Index < GetSlotCount(); Index++) 
	{
		const FItemStruct& SlotItem = InventoryItems[Index];

		if (SlotItem.Quantity < 1) return Index;

		if (Item.ItemName == SlotItem.ItemName) return Index;
	}

	return -1;
}

const TArray<FItemStruct>& UInventoryComponent::GetInventoryItems() const
{
	return InventoryItems;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	FItemStruct DefaultItem;
	InventoryItems.Init(DefaultItem, GetSlotCount());
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

