// Copyright BCV Games LLC 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/UnrealString.h"
#include "SteabloCPP/Components/StatsComponent.h"

#include "ItemInformation.generated.h"

UENUM(BlueprintType)
enum class EItemSlot : uint8
{
	Head UMETA(DisplayName = "Head"),
	Shoulders UMETA(DisplayName = "Shoulders"),
	Chest UMETA(DisplayName = "Chest"),
	Hands UMETA(DisplayName = "Hands"),
	Waist UMETA(DisplayName = "Waist"),
	Legs UMETA(DisplayName = "Legs"),
	Feet UMETA(DisplayName = "Feet"),
	MHand UMETA(DisplayName = "Main Hand"),
	OHand UMETA(DisplayName = "Off Hand"),
	THand UMETA(DisplayName = "Two Hand"),
	RRing UMETA(DisplayName = "Right Ring"),
	LRing UMETA(DisplayName = "Left Ring"),
	Neck UMETA(DisplayName = "Neck"),
	MAX,
};

USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString itemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString itemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemSlot itemSlot;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EStatName, FStat> itemStats;

    //UStatsComponent* itemStats;

	UPROPERTY(VisibleAnywhere)
	int32 itemId;

	// TODO: Need to do this better
	bool operator==(const FItemInfo &other) const
	{
		if (itemName == other.itemName
		&& itemDescription == other.itemDescription)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

/**
 * 
 */
UCLASS(Blueprintable)
class STEABLOCPP_API UItemInformation : public UObject
{
	GENERATED_BODY()
};
