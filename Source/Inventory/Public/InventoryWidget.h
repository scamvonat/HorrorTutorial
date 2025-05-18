// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "InputCoreTypes.h"
#include "Input/Events.h"

#include "InventorySlotWidget.h"
#include "ItemStruct.h"
#include "TooltipWidget.h"

#include "InventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryClose);

/**
 * 
 */
UCLASS()
class INVENTORY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(int32 Cols, int32 Rows, TSubclassOf<UInventorySlotWidget> SlotWidgetClass);

	void UpdateSlot(int32 SlotIndex, UTexture2D* SlotTexture, int32 Quantity);

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryClose OnInventoryClose;

	UPROPERTY(BlueprintAssignable)
	FOnHoverSlot OnMouseEnterSlot;

	UPROPERTY(BlueprintAssignable)
	FOnHoverSlot OnMouseLeaveSlot;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SetSlotTooltip(const FText& Label, const FText& Description, UTexture2D* Texture2D);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SetSlotTooltipVisibility(ESlateVisibility TooltipVisibility);
protected:
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* InventoryGridPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainCanvas = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTooltipWidget* Tooltip = nullptr;

	UPROPERTY()
	TArray<UInventorySlotWidget*> InventorySlots;

	UPROPERTY()
	UTooltipWidget* InventoryTooltipWidget = nullptr;

	UFUNCTION()
	void _OnMouseEnterSlot(int32 Index);
	
	UFUNCTION()
	void _OnMouseLeaveSlot(int32 Index);
};
