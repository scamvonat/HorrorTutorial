// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")	
	void OnInteractionStarted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteractionEnded();
};
