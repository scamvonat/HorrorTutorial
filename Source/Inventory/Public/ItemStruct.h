

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
};
