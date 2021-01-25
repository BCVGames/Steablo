// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>
#include "SteabloCPP/Components/InventoryComponent.h"
#include "SteabloCPP/Components/EquipmentComponent.h"
#include "SteabloCPP/Components/StatsComponent.h"
#include "SteabloCPP/SteabloCharacter.h"
#include <Math/UnrealMathUtility.h>

#include "Kismet/GameplayStatics.h"
#include "SteabloCPP/SteabloCPPPlayerController.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root Component
	itemRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(itemRootComponent);

	// Our item mesh
	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMeshComponent->SetupAttachment(itemRootComponent);

	//StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	// Set all stats to 0
	//StatsComponent->SetStats();

	ourRotator = FRotator::ZeroRotator;
	
	ourRotator.Yaw = 25.0f;

    // Physical Stats
 //   itemInformation.itemStats.Add(EStatName::Fortitude, FStat("Fortitude", 0, "How much health you have."));
	//itemInformation.itemStats.Add(EStatName::Strength, FStat("Strength", 0, "Affects damage with physical attacks."));
	//itemInformation.itemStats.Add(EStatName::Precision, FStat("Precision", 0, "Physical Critical Hit Chance"));
	//itemInformation.itemStats.Add(EStatName::Vigor, FStat("Vigor", 0, "Health Regeneration"));

 //   // Magical Stats
	//itemInformation.itemStats.Add(EStatName::Intelligence, FStat("Intelligence", 0, "How much mana you have."));
	//itemInformation.itemStats.Add(EStatName::Will, FStat("Will", 0, "Affects damage with magical attacks."));
	//itemInformation.itemStats.Add(EStatName::Alacrity, FStat("Alacrity", 0, "Magical Critical Hit Chance"));
	//itemInformation.itemStats.Add(EStatName::Vim, FStat("Vim", 0, "Mana Regeneration"));

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	//sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::BeginOverlap);
	//staticMeshComponent->OnClicked.AddDynamic(this, &ABaseItem::ItemOnClicked);

    for (auto It = itemInformation.itemStats.CreateConstIterator(); It; ++It)
    {
        if (It->Value.baseValue == 0)
        {
			itemInformation.itemStats.Remove(It->Key);
        }
    }

}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	itemRootComponent->AddLocalRotation(ourRotator*DeltaTime);
}

/// <summary>
/// Rolls the stats based on min/max values;
/// </summary>
void ABaseItem::RollStats()
{
	int32 newValue;
	int32 mod;
    for (TPair<EStatName, FStat>& kvp : itemInformation.itemStats)
    {
		newValue = kvp.Value.baseValue;
		mod = kvp.Value.statMod; // For Items, I use the statMod as a +/- for a random range: A base of 2 with a mod of 1 in the blueprint will give you a range of 1-3 for the stat.

		newValue = FMath::RandRange(newValue - mod, newValue + mod);
		kvp.Value.baseValue = newValue;
    }
}

void ABaseItem::Pickup(ASteabloCharacter* pickerUpper)
{
	if (!pickerUpper->Equipment->EquipItem(this))
	{
		pickerUpper->Inventory->AddItem(this);
	}
	Destroy();
}
