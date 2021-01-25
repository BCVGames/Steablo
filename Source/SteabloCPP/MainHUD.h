// Copyright BCV Games LLC 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class STEABLOCPP_API AMainHUD : public AHUD
{
	GENERATED_BODY()
#pragma region Variables
public:
	//class UProgressBar* hpBar;
#pragma endregion

#pragma region Functions
public:
	void BeginPlay() override;
	void Tick(float deltaSeconds) override;
private:
	// Main drawing function
	virtual void DrawHUD() override;

#pragma endregion 
};
