// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/DataValidation.h"

#include "ItemUtils.h"
#include "InventoryEventStruct.h"

#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	int32 GetColCount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRowCount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetSlotCount() const;

	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemStruct& Item);

	UFUNCTION(BlueprintCallable)
	int32 GetSlotForItem(const FItemStruct& Item) const;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryAdd OnAddItem;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryRemove OnRemoveItem;

	UFUNCTION()
	const TArray<FItemStruct>& GetInventoryItems() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Getter)
	TArray<FItemStruct> InventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Rows = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cols = 5;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
