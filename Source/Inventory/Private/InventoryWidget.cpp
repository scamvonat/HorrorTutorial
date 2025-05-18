// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::Init(int32 Cols, int32 Rows, TSubclassOf<UInventorySlotWidget> SlotWidgetClass)
{
	if (!IsValid(SlotWidgetClass) || !IsValid(InventoryGridPanel)) return;

	for(int32 i = 0; i < Rows; ++i)
	{
		for (int32 j = 0; j < Cols; ++j)
		{
			int32 Index = i * Cols + j;
			
			UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
			if (SlotWidget)
			{
				UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(SlotWidget);

				if(IsValid(GridSlot))
				{
					GridSlot->SetRow(i);
					GridSlot->SetColumn(j);
				}

				SlotWidget->OnMouseEnterSlot.AddDynamic(this, &UInventoryWidget::_OnMouseEnterSlot);
				SlotWidget->OnMouseLeaveSlot.AddDynamic(this, &UInventoryWidget::_OnMouseLeaveSlot);

				SlotWidget->SetSlotIndex(Index);
				InventorySlots.Add(SlotWidget);
			}
		}
	}
	
	if (IsValid(Tooltip))
	{
		Tooltip->SetVisibility(ESlateVisibility::Hidden);
	}

	SetIsFocusable(true);
}

void UInventoryWidget::UpdateSlot(int32 SlotIndex,	UTexture2D* SlotTexture, int32 Quantity)
{
	if (!InventorySlots.IsValidIndex(SlotIndex)) return;
	
	UInventorySlotWidget* SlotWidget = InventorySlots[SlotIndex];
	
	if (!IsValid(SlotWidget)) return;

	SlotWidget->SetItemImage(SlotTexture);
	SlotWidget->SetItemQuantity(Quantity);
}

void UInventoryWidget::SetSlotTooltip(const FText& Label, const FText& Description, UTexture2D* Texture2D)
{
	Tooltip->SetLabel(Label);
	Tooltip->SetDescription(Description);
	Tooltip->SetTexture(Texture2D);

	float MouseX, MouseY;
	UWorld* World = GetWorld();

	World->GetFirstPlayerController()->GetMousePosition(MouseX, MouseY);
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Tooltip->Slot);

	CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
	FVector2D ScreenPosition(MouseX, MouseY);
	FGeometry Geometry = MainCanvas->GetCachedGeometry();
	FVector2D LocalPosition = Geometry.AbsoluteToLocal(ScreenPosition);
	CanvasSlot->SetPosition(LocalPosition);
}

void UInventoryWidget::SetSlotTooltipVisibility(ESlateVisibility TooltipVisibility)
{
	Tooltip->SetVisibility(TooltipVisibility);
}

FReply UInventoryWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		float MouseX, MouseY;
		UWorld* World = GetWorld();

		World->GetFirstPlayerController()->GetMousePosition(MouseX, MouseY);
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Tooltip->Slot);
		
		CanvasSlot->SetAlignment(FVector2D(0.0f, -1.0f));
		FVector2D ScreenPosition(MouseX, MouseY);
		FGeometry Geometry = MainCanvas->GetCachedGeometry();
		FVector2D LocalPosition = Geometry.AbsoluteToLocal(ScreenPosition);
		CanvasSlot->SetPosition(LocalPosition);
	}
	
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		OnInventoryClose.Broadcast();
		return FReply::Handled();
	}
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UInventoryWidget::_OnMouseEnterSlot(int32 Index)
{
	OnMouseEnterSlot.Broadcast(Index);
}

void UInventoryWidget::_OnMouseLeaveSlot(int32 Index)
{
	OnMouseLeaveSlot.Broadcast(Index);
}
