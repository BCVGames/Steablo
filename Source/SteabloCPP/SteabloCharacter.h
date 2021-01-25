// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteabloCPPCharacter.h"
#include "Items/BaseItem.h"
#include "SteabloCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STEABLOCPP_API ASteabloCharacter : public ASteabloCPPCharacter 
{
	GENERATED_BODY()

public:
#pragma region Members
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UEquipmentComponent* Equipment;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	class UStatsComponent* StatsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float maxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float currentMana;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float maxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float regenTick;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float regenTimer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float attackTime;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float attackTimer;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float attackRange;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float pickupRadius;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Status")
	bool isAttacking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
    int currentLevel;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
    int32 currentExp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
    TMap<int, int> experienceMap;

private:
	float hpModifier;
	float mpModifier;
    bool canAttack;
    bool bMouseDown;
#pragma endregion
	
#pragma region Functions
public:
	ASteabloCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Modifiers
	UFUNCTION(BlueprintCallable)
	void ModifyHealth(float amtToModify);

    UFUNCTION(BlueprintCallable)
    void ModifyMana(float amtToModify);

    UFUNCTION(BlueprintCallable)
    void ModifyExp(int amtToModify);
#pragma endregion 
#pragma region Getters
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable)
	float GetManaPercent() const;

    UFUNCTION(BlueprintGetter)
    float GetXpPercent() const;

    UFUNCTION(BlueprintGetter)
    FText GetHPStatusString() const;

    UFUNCTION(BlueprintGetter)
    FText GetMPStatusString() const;

    UFUNCTION(BlueprintGetter)
    FText GetXPStatusString() const;
#pragma endregion 

#pragma region Blueprint Implements
    UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
    void OnAttackBP(class ABaseEnemy* target);
    UFUNCTION(BlueprintImplementableEvent, Category = "Experience")
    void OnLevelUpBP();
#pragma endregion 
	void ApplyItemStats(FItemInfo itemInfo);
	void RemoveItemStats(FItemInfo itemInfo);

    void Attack(class ABaseEnemy* target);

	bool CheckAttackRange(float distToCheck);
	bool CheckPickupRadius(float distToCheck);

private:
	void CalcStats();
    void LevelUp();
#pragma endregion 
};
