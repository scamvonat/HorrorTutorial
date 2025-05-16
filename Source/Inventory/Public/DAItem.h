// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DAItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UDAItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ClampMin = "1"))
	int32 MaxQuantity;
};
