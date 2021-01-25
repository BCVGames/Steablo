// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteabloCPPGameMode.h"
#include "SteabloCPPPlayerController.h"
#include "SteabloCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASteabloCPPGameMode::ASteabloCPPGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASteabloCPPPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SteabloCPP/Blueprints/Player/BP_SteabloCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}