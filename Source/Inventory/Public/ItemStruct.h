

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct INVENTORY_API FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Quantity;

	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override {
		EDataValidationResult Result = EDataValidationResult::Valid;

		if(ItemName.IsNone())
		{
			Result = EDataValidationResult::Invalid;
		}

		if(Quantity < 1) 	
		{
			Result = EDataValidationResult::Invalid;
		}

		return Result;
	}
};