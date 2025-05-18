// Fill out your copyright notice in the Description page of Project Settings.


#include "TooltipWidget.h"

void UTooltipWidget::SetLabel(const FText& NewLabel)
{
	Label->SetText(NewLabel);
}

void UTooltipWidget::SetDescription(const FText& NewDescription)
{
	Description->SetText(NewDescription);
}

void UTooltipWidget::SetTexture(UTexture2D* NewTexture)
{
	Image->SetBrushFromTexture(NewTexture);
}
