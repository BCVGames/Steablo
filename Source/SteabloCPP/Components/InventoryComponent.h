// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Items/BaseItem.h"
#include "InventoryComponent.generated.h"

const int MaxInventory = 60;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEABLOCPP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables
public:
		UPROPERTY(EditAnywhere, Category = "Inventory")
		TArray<FItemInfo> itemsInInv;
#pragma endregion
	
#pragma region Functions
public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddItem(ABaseItem* itemToAdd);
	void RemoveItem(ABaseItem* itemToRemove);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion 
};
