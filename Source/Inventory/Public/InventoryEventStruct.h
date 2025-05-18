// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemStruct.h"

#include "InventoryEventStruct.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlotBaseEvent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FItemStruct Slot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bIsEmpty;
};

USTRUCT(BlueprintType)
struct FInventoryAddEvent : public FInventorySlotBaseEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FItemStruct AddedItem;
};

USTRUCT(BlueprintType)
struct FInventoryRemoveEvent : public FInventorySlotBaseEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FItemStruct RemovedItem;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryAdd, FInventoryAddEvent, EventData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryRemove, FInventoryRemoveEvent, EventData);