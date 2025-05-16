// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	PlayAnimationForward(HoverAnimation);
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	PlayAnimationReverse(HoverAnimation);
}

void UInventorySlotWidget::SetItemQuantity(int32 Quantity)
{
	QuantityText->SetText(FText::AsNumber(Quantity));
	QuantityText->SetVisibility(Quantity > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UInventorySlotWidget::SetItemImage(UTexture2D* Texture)
{
	if (Texture)
	{
		Image->SetBrushFromTexture(Texture);
		Image->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Image->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	QuantityText->SetVisibility(ESlateVisibility::Hidden);
	QuantityText->SetText(FText::AsNumber(0));

	Image->SetVisibility(ESlateVisibility::Hidden);
}