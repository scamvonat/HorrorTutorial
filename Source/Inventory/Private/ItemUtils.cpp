// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUtils.h"

UDAItem* UItemUtils::GetItemByID(FName ItemID)
{
	FPrimaryAssetId AssetId = FPrimaryAssetId("Item", ItemID);

	UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
	if(!IsValid(AssetManager)) return nullptr;

	FSoftObjectPath AssetPath = AssetManager->GetPrimaryAssetPath(AssetId);

	if (!AssetPath.IsValid()) return nullptr;

	UDAItem* DataAsset = Cast<UDAItem>(AssetPath.TryLoad());
	return DataAsset;
}