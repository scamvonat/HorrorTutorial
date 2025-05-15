// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ItemStruct.h"

#include "PickableObject.generated.h"

UCLASS()
class INVENTORY_API APickableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanBePickedUp() const;
	virtual bool CanBePickedUp_Implementation() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PickUp();
	virtual void PickUp_Implementation();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FItemStruct ItemData;

	#if WITH_EDITORONLY_DATA
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		UStaticMesh* Mesh;
	#endif

	#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
};
