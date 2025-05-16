// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"

#include "PickableObject.h"
#include "InteractionWidget.h"
#include "InventoryWidget.h"
#include "InventorySlotWidget.h"

#include "PlayerInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UPlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void SetCanLoot(bool bCanLoot);

	UFUNCTION(BlueprintCallable)
	void PickUp();

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CheckLooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass = nullptr;

	UPROPERTY()
	UInteractionWidget* InteractionWidget = nullptr;

	bool bIsCanLoot = true;

	UPROPERTY()
	APickableObject* CurrentLootingObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass = nullptr;

	UPROPERTY()
	UInventoryWidget* InventoryWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UInventorySlotWidget> InventorySlotWidgetClass = nullptr;

	UPROPERTY()
	TArray<UInventorySlotWidget*> InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cols = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Rows = 5;


	void SetCurrentLootingObject(APickableObject* LootingObject);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
