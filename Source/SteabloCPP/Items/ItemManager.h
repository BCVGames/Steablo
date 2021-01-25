// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseItem.h"
#include "CoreMinimal.h"
#include "ItemInformation.h"
#include "GameFramework/Actor.h"
#include "ItemManager.generated.h"

UCLASS()
class STEABLOCPP_API AItemManager : public AActor
{
	GENERATED_BODY()

#pragma region Variables
public:
    UPROPERTY(EditAnywhere, Category = Items, meta = (AllowPrivateAccess = "true", EditInline = true))
    TArray<TSubclassOf<ABaseItem>> ItemBlueprints;  
protected:
private:
	int32 currentId;
#pragma endregion
	
#pragma region Functions
public:	
	// Sets default values for this actor's properties
	AItemManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnItem(FVector location = FVector(-0, 100, 100));
#pragma endregion 
};
