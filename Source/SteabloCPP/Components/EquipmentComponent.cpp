// Copyright BCV Games LLC 2020


#include "EquipmentComponent.h"
#include "StatsComponent.h"
#include "SteabloCPP/SteabloCharacter.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ourCharacter = Cast<ASteabloCharacter>(GetOwner());
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEquipmentComponent::EquipItem(ABaseItem* itemToEquip)
{
	if (!equippedItems.Contains(itemToEquip->itemInformation.itemSlot))
	{
		equippedItems.Add(itemToEquip->itemInformation.itemSlot, itemToEquip->itemInformation);
		ourCharacter->ApplyItemStats(itemToEquip->itemInformation);
		return true;
	}
	else
	{
		return false;
	}
}

FItemInfo UEquipmentComponent::SwapItem(ABaseItem* itemToSwap)
{
	FItemInfo itemSwappedOut = equippedItems.FindAndRemoveChecked(itemToSwap->itemInformation.itemSlot);
	ourCharacter->RemoveItemStats(itemSwappedOut);

    equippedItems.Add(itemToSwap->itemInformation.itemSlot, itemToSwap->itemInformation);
    ourCharacter->ApplyItemStats(itemToSwap->itemInformation);

	return itemSwappedOut;
}

FItemInfo UEquipmentComponent::GetItemInfo(EItemSlot slotToCheck)
{
	if (equippedItems.Contains(slotToCheck))
	{
		return equippedItems[slotToCheck];
	}
	else
	{
		return FItemInfo();
	}
}

