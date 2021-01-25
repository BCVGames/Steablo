// Copyright BCV Games LLC 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SteabloCPP/SteabloCharacter.h"
#include "SteabloCPP/Items/ItemInformation.h"

#include "EquipmentComponent.generated.h"


class ABaseItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEABLOCPP_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<EItemSlot, FItemInfo> equippedItems;
protected:

private:
	class ASteabloCharacter* ourCharacter;
#pragma endregion 

#pragma region Functions
public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Attempt to equip the supplied item
	/// </summary>
	/// <param name="itemToEquip">The item we are trying to equip</param>
	/// <returns>Whether item was successfully equipped</returns>
	bool EquipItem(class ABaseItem* itemToEquip);

	/// <summary>
	/// Swap an item into an equipment slot
	/// </summary>
	/// <param name="itemToSwap">The item to swap in</param>
	/// <returns>The item was was in the slot before swapping</returns>
	FItemInfo SwapItem(class ABaseItem* itemToSwap);

	UFUNCTION(BlueprintCallable)
	FItemInfo GetItemInfo(EItemSlot slotToCheck);
#pragma endregion
		
};
