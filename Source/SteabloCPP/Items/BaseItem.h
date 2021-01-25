// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInformation.h"
#include <Math/Rotator.h>
#include "BaseItem.generated.h"

UCLASS(Abstract)
class STEABLOCPP_API ABaseItem : public AActor
{
	GENERATED_BODY()
#pragma region Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Information", meta = (EditInline = true))
	FItemInfo itemInformation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	class USceneComponent* itemRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* staticMeshComponent;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    //class UStatsComponent* StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotation")
	FRotator ourRotator;
#pragma endregion

#pragma region Functions
public:
	// Sets default values for this actor's properties
	ABaseItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void RollStats();

	void Pickup(class ASteabloCharacter* pickerUpper);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
#pragma endregion 
};
