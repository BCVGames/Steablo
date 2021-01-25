// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"


#include "BaseItem.h"
#include "Engine/ObjectLibrary.h"


// Sets default values
AItemManager::AItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemManager::SpawnItem(FVector location)
{
	UObjectLibrary* ObjLib = UObjectLibrary::CreateLibrary(ABaseItem::StaticClass(), true, GIsEditor);
	FString SubPath;
    UClass* ChosenSpawnItemClass = nullptr;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attempting Item Spawn!"));


	switch(FMath::RandRange(0, 3))
	{
        case 0:
            SubPath = "Armor";
            break;
		case 1:
			SubPath = "Offhands";
			break;
        case 2:
            SubPath = "Weapons";
            break;
        case 3:
            SubPath = "Jewelry";
            break;
        default:
            SubPath = "Armor";
            break;
	}

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SubPath is: " + SubPath));


    //Create object library 
    TArray<FAssetData> AssetDatas;
    FAssetData ChosenAssetData;
	ObjLib->AddToRoot();
    ObjLib->LoadBlueprintAssetDataFromPath(TEXT("/Game/SteabloCPP/Blueprints/Items/" + SubPath));
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, fullPath);

    ObjLib->GetAssetDataList(AssetDatas);


    if (AssetDatas.Num() > 0)
    {
        if (AssetDatas.Num() == 1)
        {
            //Get the only Asset in this folder
            ChosenAssetData = AssetDatas[0];
        }
        else
        {
            //Choose random asset from suitable ones
            ChosenAssetData = AssetDatas[FMath::RandRange(0, AssetDatas.Num()-1)] ;
        }

        //Load class from chosen (unloaded) asset/class
        FString LoadClassString = ChosenAssetData.ToSoftObjectPath().ToString() + "_C";
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Class string is: " + LoadClassString));
        ChosenSpawnItemClass = LoadClass<ABaseItem>(NULL, *LoadClassString, NULL, LOAD_None, NULL);
    }

    // SPAWN ITEM
    if (ChosenSpawnItemClass != nullptr)
    {
        FActorSpawnParameters SpawnInfo;

        ABaseItem* SpawnedItem = GetWorld()->SpawnActor<ABaseItem>(ChosenSpawnItemClass, SpawnInfo);
        SpawnedItem->RollStats();
        SpawnedItem->SetActorLocation(location);
        //return SpawnedItem->itemInformation;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpawnItemClass pointer was shit"));
    }
}

