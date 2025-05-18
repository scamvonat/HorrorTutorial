// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/AssetManager.h"

#include "DAItem.h"

#include "ItemUtils.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UItemUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static UDAItem* GetItemByID(FName ItemID);
};
