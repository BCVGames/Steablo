// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SteabloCPPPlayerController.generated.h"

UCLASS()
class ASteabloCPPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASteabloCPPPlayerController();
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	UPROPERTY(VisibleAnywhere)
	bool bReachedDestination;
    UPROPERTY(VisibleAnywhere)
    FVector lastTargetedPos;

	AActor* targetedActor;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Nagivate player to the last known target if we arent holding down the mouse button */
	void MoveToLastTarget();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	


	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};


