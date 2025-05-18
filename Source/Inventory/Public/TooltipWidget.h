// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "TooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UTooltipWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetLabel(const FText& NewLabel);

	UFUNCTION()
	void SetDescription(const FText& NewLabel);

	UFUNCTION()
	void SetTexture(UTexture2D* NewLabel);
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Label = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* Image = nullptr;
};
