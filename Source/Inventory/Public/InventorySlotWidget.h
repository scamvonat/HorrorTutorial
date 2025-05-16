// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemQuantity(int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemImage(UTexture2D* Texture);
	
protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HoverAnimation = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* Image = nullptr;

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
