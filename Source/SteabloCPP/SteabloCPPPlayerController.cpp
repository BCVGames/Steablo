// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteabloCPPPlayerController.h"

#include "BaseEnemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SteabloCPPCharacter.h"
#include "Engine/World.h"
#include "Items/BaseItem.h"
#include "Kismet/KismetMathLibrary.h"
#include "SteabloCharacter.h"

ASteabloCPPPlayerController::ASteabloCPPPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;
	bEnableClickEvents = true;
	bReachedDestination = true;
	targetedActor = nullptr;
}

void ASteabloCPPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	else
	{
		MoveToLastTarget();
	}
}

void ASteabloCPPPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASteabloCPPPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASteabloCPPPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASteabloCPPPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASteabloCPPPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ASteabloCPPPlayerController::OnResetVR);
}

void ASteabloCPPPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASteabloCPPPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ASteabloCPPCharacter* MyPawn = Cast<ASteabloCPPCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
                UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		targetedActor = Hit.GetActor();

		if (Cast<ABaseEnemy>(Hit.Actor) || Cast<ABaseItem>(Hit.Actor))
		{
            APawn* const MyPawn = GetPawn();
            if (MyPawn)
            {
				FRotator lookatRot = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Actor->GetActorLocation());
				lookatRot.Pitch = 0.0f;
				lookatRot.Roll = 0.0f;
				MyPawn->SetActorRotation(lookatRot);
                ABaseItem* item = Cast<ABaseItem>(targetedActor);
                ABaseEnemy* enemy = Cast<ABaseEnemy>(targetedActor);
				ASteabloCharacter* player = Cast<ASteabloCharacter>(MyPawn);
				if (enemy)
				{
					float const distance = FVector::Dist(enemy->GetActorLocation(), MyPawn->GetActorLocation());
					if (player->CheckAttackRange(distance))
					{
					    // We click an enemy and are already within attack range
						player->Attack(enemy);
						return;
					}
				}
				else if (item)
				{
                    float const distance = FVector::Dist(item->GetActorLocation(), MyPawn->GetActorLocation());
                    if (player->CheckPickupRadius(distance))
                    {
                        // We click an enemy and are already within attack range
						item->Pickup(player);
						return;
                    }
				}
            }
		}

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ASteabloCPPPlayerController::MoveToLastTarget()
{
	if (false == bReachedDestination)
	{
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			float const Distance = FVector::Dist(lastTargetedPos, MyPawn->GetActorLocation());

			// We need to issue move command only if far enough in order for walk animation to play correctly
			if ((Distance > 120.0f))
			{
				//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
				MyPawn->AddMovementInput(lastTargetedPos - MyPawn->GetActorLocation());
			}
			else
			{
				// We have arrived within range of our target
				bReachedDestination = true;
                ABaseItem* item = Cast<ABaseItem>(targetedActor);
                ABaseEnemy* enemy = Cast<ABaseEnemy>(targetedActor);
                ASteabloCharacter* player = Cast<ASteabloCharacter>(MyPawn);
                if (enemy)
                {
                    float const distance = FVector::Dist(enemy->GetActorLocation(), MyPawn->GetActorLocation());
                    if (player->CheckAttackRange(distance))
                    {
                        // We click an enemy and are already within attack range
                        player->Attack(enemy);
                    }
                }
                else if (item)
                {
                    float const distance = FVector::Dist(item->GetActorLocation(), MyPawn->GetActorLocation());
                    if (player->CheckPickupRadius(distance))
                    {
                        // We click an enemy and are already within attack range
                        item->Pickup(player);
                    }
                }
			}
		}
	}
}

void ASteabloCPPPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASteabloCPPPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
            //UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			lastTargetedPos = DestLocation;
			bReachedDestination = false;
            MyPawn->AddMovementInput(DestLocation - MyPawn->GetActorLocation());
		}
	}
}

void ASteabloCPPPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ASteabloCPPPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
