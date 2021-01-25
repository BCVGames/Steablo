// Copyright BCV Games LLC 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Containers/Map.h>
#include "StatsComponent.generated.h"

#pragma region Enums and Structs
UENUM()
enum class EStatName : uint8
{
	// How much health you have
	Fortitude UMETA(DisplayName = "Fortitude"),

	// How much mana you have
	Intelligence UMETA(DisplayName = "Intelligence"),

	// Physical Damage
	Strength UMETA(DisplayName = "Strength"),

	// Magical Damage
	Will UMETA(DisplayName = "Will"),

	// Health Regeneration
	Vigor UMETA(DisplayName = "Vigor"),

	// Mana Regeneration
	Vim UMETA(DisplayName = "Vim"),

	// Physical Critical Hit Chance
	Precision UMETA(DisplayName = "Precision"),

	// Magical Critical Hit Chance
	Alacrity UMETA(DisplayName = "Alacrity"),

	AttackSpeed UMETA(DisplayName = "Attack Speed"),
};

USTRUCT(BlueprintType)
/// <summary>
/// A single stat.
/// </summary>
struct FStat
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString statName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString statDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 baseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 statMod;
	FStat()
	{
		FStat(TEXT("Unnamed Stat"), 0);
	}

	FStat(FString name, int32 startingValue, FString description = "No description")
	{
		statName = name;
		statDescription = description;
		baseValue = startingValue;
		statMod = 0;
	}

	/// <summary>
	/// Gets the current value of the stat, base + mods
	/// </summary>
	/// <returns></returns>
	int32 GetCurrentValue() const
	{
		return baseValue + statMod;
	}
	   
};
#pragma endregion


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEABLOCPP_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables
public:
    UPROPERTY(EditAnywhere, Category = "Stats")
	TMap<EStatName, FStat> Stats;
#pragma endregion

#pragma region Functions
public:	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Custom functions
	void ModStat(EStatName statToMod, int modAmt);

	UFUNCTION(BlueprintPure, Category = "Stats")
	int32 GetStatValue(EStatName statValToGet) const;


	void SetStats(int32 fort = 0, int32 intel = 0, int32 str = 0, int32 will = 0, int32 prec = 0, int32 alac = 0, int32 vigor = 0, int32 vim = 0);
#pragma endregion
		
};
