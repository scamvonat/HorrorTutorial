// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "InventorySlotWidget.h"

#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void Init(int32 Cols, int32 Rows, TSubclassOf<UInventorySlotWidget> SlotWidgetClass);

protected:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* InventoryGridPanel = nullptr;

	UPROPERTY()
	TArray<UInventorySlotWidget*> InventorySlots;
};
