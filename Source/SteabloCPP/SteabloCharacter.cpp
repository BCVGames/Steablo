// Fill out your copyright notice in the Description page of Project Settings.


#include "SteabloCharacter.h"

#include "SteabloCPPPlayerController.h"
#include "Components/InventoryComponent.h"
#include "Components/EquipmentComponent.h"
#include "Components/StatsComponent.h"
#include "Kismet/GameplayStatics.h"
#include <Internationalization/Internationalization.h>
#include "BaseEnemy.h"
#include "Kismet/KismetMathLibrary.h"

ASteabloCharacter::ASteabloCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup our components
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Equipment = CreateDefaultSubobject<UEquipmentComponent>("Equipment");
	StatsComponent = CreateDefaultSubobject<UStatsComponent>("Stats");

	// Init 
	regenTimer = 0.f;
	regenTick = 0.1f;
	hpModifier = 10.f;
	mpModifier = 10.f;

	CalcStats();
	currentHealth = maxHealth;
	currentMana = maxMana;

	attackRange = 800.0f;
	pickupRadius = 250.0f;

	attackTimer = 0.f;
	attackTime = 0.7f;
	isAttacking = false;
	canAttack = true;

	currentExp = 0;
	currentLevel = 1;
    experienceMap.Add(1, 0);
    experienceMap.Add(2, 100);

	for(int i = 2; i < 25; i++)
	{
		experienceMap.Add(currentLevel + i, experienceMap[i]*.5f + (experienceMap[i] * 1.05));
	}
}

void ASteabloCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region Regen
	regenTimer += DeltaTime;

	if (regenTimer >= regenTick)
	{
		regenTimer = 0.f;
		if (currentHealth < maxHealth)
		{
			ModifyHealth(StatsComponent->GetStatValue(EStatName::Vigor) * regenTick);
		}
		if (currentMana < maxMana)
		{
            ModifyMana(StatsComponent->GetStatValue(EStatName::Vim) * regenTick);
		}
	}
#pragma endregion

#pragma region Attacking
	if (!canAttack)
	{
		attackTimer += DeltaTime;
		if (attackTimer >= attackTime)
		{
			canAttack = true;
		}
	}
#pragma endregion 


}

#pragma region Modifiers
/// <summary>
/// Modify the characters health pool.
/// </summary>
/// <param name="amtToModify">This should be negative to do damage :)</param>
void ASteabloCharacter::ModifyHealth(float amtToModify)
{
	currentHealth += amtToModify;
	currentHealth = FMath::Clamp(currentHealth, 0.f, maxHealth);

    // TODO: Check if we died...
}

/// <summary>
/// Modify the characters health pool.
/// </summary>
/// <param name="amtToModify">This should be negative to do remove mana :)</param>
void ASteabloCharacter::ModifyMana(float amtToModify)
{
    currentMana += amtToModify;
	currentMana = FMath::Clamp(currentMana, 0.f, maxMana);

    // TODO: Check if we died...
}

void ASteabloCharacter::ModifyExp(int amtToModify)
{
	currentExp += amtToModify;
	while (currentExp >= experienceMap[currentLevel+1])
	{
		LevelUp();
	}
}
#pragma endregion 

#pragma region Getters
float ASteabloCharacter::GetHealthPercent() const
{
	return currentHealth / maxHealth;
}

float ASteabloCharacter::GetManaPercent() const
{
	return currentMana / maxMana;
}

float ASteabloCharacter::GetXpPercent() const
{
	return static_cast<float>(currentExp - experienceMap[currentLevel]) / static_cast<float>(experienceMap[currentLevel + 1] - experienceMap[currentLevel]);
}

FText ASteabloCharacter::GetHPStatusString() const
{
	return FText::Format(NSLOCTEXT("StatusText", "Status", "{0} / {1}"), FMath::TruncToInt(currentHealth), maxHealth);
}

FText ASteabloCharacter::GetMPStatusString() const
{
    return FText::Format(NSLOCTEXT("StatusText", "Status", "{0} / {1}"), FMath::TruncToInt(currentMana), maxMana);
}

FText ASteabloCharacter::GetXPStatusString() const
{
	return FText::Format(NSLOCTEXT("StatusText", "Status", "{0} / {1}"), currentExp, experienceMap[currentLevel + 1]);
}

#pragma endregion
#pragma region Item Application
void ASteabloCharacter::ApplyItemStats(FItemInfo itemInfo)
{
    for (TPair<EStatName, FStat>& kvp : itemInfo.itemStats)
    {
        StatsComponent->ModStat(kvp.Key, kvp.Value.baseValue);
    }
	CalcStats();
}

void ASteabloCharacter::RemoveItemStats(FItemInfo itemInfo)
{
    for (TPair<EStatName, FStat>& kvp : itemInfo.itemStats)
    {
        StatsComponent->ModStat(kvp.Key, -kvp.Value.baseValue);
    }
    CalcStats();
}
#pragma endregion


void ASteabloCharacter::CalcStats()
{
	maxHealth = StatsComponent->GetStatValue(EStatName::Fortitude) * hpModifier;
	maxMana = StatsComponent->GetStatValue(EStatName::Intelligence) * mpModifier;
}

void ASteabloCharacter::LevelUp()
{
	// Let BP know we leveledup, so we can celebrate it appropriately
    OnLevelUpBP();
    currentLevel++;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Congratulations!  You've reached level %d!"), currentLevel));

    StatsComponent->ModStat(EStatName::Fortitude, 2);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Fortitude!"), 2));
    StatsComponent->ModStat(EStatName::Intelligence, 2);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Intelligence!"), 2));
    StatsComponent->ModStat(EStatName::Strength, 2);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Strength!"), 2));
    StatsComponent->ModStat(EStatName::Will, 2);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Will!"), 2));

	if (currentLevel % 2 == 0)
	{
        StatsComponent->ModStat(EStatName::Vigor, 1);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Vigor!"), 1));
        StatsComponent->ModStat(EStatName::Vim, 1);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Vim!"), 1));
        StatsComponent->ModStat(EStatName::Precision, 1);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Precision!"), 1));
        StatsComponent->ModStat(EStatName::Alacrity, 1);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You gained %d Alacrity!"), 1));
    }

	CalcStats();
	currentHealth = maxHealth;
}

void ASteabloCharacter::Attack(ABaseEnemy* target)
{
	float weaponDamage = StatsComponent->GetStatValue(EStatName::Strength);  // TODO: Generate some real info from weapons
	if (canAttack)
	{
		// Check for a critical hit (physical atm)
		if (FMath::RandRange(0, 100) <= StatsComponent->GetStatValue(EStatName::Precision))
		{
			weaponDamage *= 2.0f;
		}
        OnAttackBP(target);
        target->ModifyHealth(-weaponDamage, this);
		isAttacking = true;
		canAttack = false;
		attackTimer = 0.0f;
	}
}

bool ASteabloCharacter::CheckAttackRange(float distToCheck)
{
	return distToCheck <= attackRange;
}

bool ASteabloCharacter::CheckPickupRadius(float distToCheck)
{
	return distToCheck <= pickupRadius;
}

