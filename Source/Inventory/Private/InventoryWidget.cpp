// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::Init(int32 Cols, int32 Rows, TSubclassOf<UInventorySlotWidget> SlotWidgetClass)
{
	if (!IsValid(SlotWidgetClass) || !IsValid(InventoryGridPanel)) return;

	for(int32 i = 0; i < Cols; ++i)
	{
		for (int32 j = 0; j < Rows; ++j)
		{
			UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
			if (SlotWidget)
			{
				UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(SlotWidget);

				if(IsValid(GridSlot))
				{
					GridSlot->SetRow(j);
					GridSlot->SetColumn(i);
				}

				InventorySlots.Add(SlotWidget);
			}
		}
	}
}
