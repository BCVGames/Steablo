// Copyright BCV Games LLC 2020


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Stats.Empty();

	/* Setting up base stats here */
	// Physical Stats
	Stats.Add(EStatName::Fortitude, FStat("Fortitude", 10, "How much health you have."));
    Stats.Add(EStatName::Strength, FStat("Strength", 10, "Affects damage with physical attacks."));
    Stats.Add(EStatName::Precision, FStat("Precision", 10, "Physical Critical Hit Chance"));
    Stats.Add(EStatName::Vigor, FStat("Vigor", 2, "Health Regeneration"));

	// Magical Stats
    Stats.Add(EStatName::Intelligence, FStat("Intelligence", 10, "How much mana you have."));
    Stats.Add(EStatName::Will, FStat("Will", 10, "Affects damage with magical attacks."));
    Stats.Add(EStatName::Alacrity, FStat("Alacrity", 10, "Magical Critical Hit Chance"));
    Stats.Add(EStatName::Vim, FStat("Vim", 2, "Mana Regeneration"));

	// Secondary Stats
	Stats.Add(EStatName::AttackSpeed, FStat("AttackSpeed", 1.0f, "Speed at which you attack"));
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::ModStat(EStatName statToMod, int modAmt)
{
	if (Stats.Contains(statToMod))
	{
		Stats[statToMod].statMod += modAmt;
	}
	else
	{
        UE_LOG(LogTemp, Warning, TEXT("StatComponent.cpp - ModStat(): Supplied stat doesnt exist."));
	}
}

int32 UStatsComponent::GetStatValue(EStatName statValToGet) const
{
	if (Stats.Contains(statValToGet))
	{
		return Stats[statValToGet].GetCurrentValue();
	}
	else
	{
        UE_LOG(LogTemp, Warning, TEXT("StatComponent.cpp - GetStatValue(): Supplied stat doesnt exist."));
		return 0;
	}
}

void UStatsComponent::SetStats(int32 fort /*= 0*/, int32 intel /*= 0*/, int32 str /*= 0*/, int32 will /*= 0*/, int32 prec /*= 0*/, int32 alac /*= 0*/, int32 vigor /*= 0*/, int32 vim /*= 0*/)
{
	Stats[EStatName::Fortitude].baseValue = fort;
    Stats[EStatName::Intelligence].baseValue = intel;
    Stats[EStatName::Strength].baseValue = str;
    Stats[EStatName::Will].baseValue = will;
    Stats[EStatName::Precision].baseValue = prec;
    Stats[EStatName::Alacrity].baseValue = alac;
    Stats[EStatName::Vigor].baseValue = vigor;
    Stats[EStatName::Vim].baseValue = vim;
}


