// Copyright BCV Games LLC 2020


#include "MainHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include <Components/ProgressBar.h>

void AMainHUD::BeginPlay()
{
	//hpBar = new UProgressBar();
	Super::BeginPlay();
}

void AMainHUD::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AMainHUD::DrawHUD()
{
	// Select the center point of the bar as the character's location
	FVector center = FVector::ZeroVector;
	// Offsets of the bar
	FVector extent = FVector(60.f, 34.f, 200.f);

	// Project function of Canvas translates a world position to the screen position
	FVector2D center2D = FVector2D(Canvas->Project(FVector(center.X, center.Y, center.Z + extent.Z)));

	float actorExtent = 33.f;
	float healthPercentage = 0.5f;
	float yOffset = 10.f;

	healthPercentage = 0.5f;
    FVector pos1 = Canvas->Project(FVector(center.X, center.Y - actorExtent * 2, center.Z + extent.Z));
	FVector pos2 = Canvas->Project(FVector(center.X, center.Y + actorExtent * 2, center.Z + extent.Z));

	float barWidth = (pos2 - pos1).Size2D();
	float barHeight = barWidth * 0.2f;

	// Draw a background color first
	/* Background tile */
	barWidth += 2.f;
	barHeight += 2.f;

	float x = center2D.X - barWidth * 0.5f;
	float y = center2D.Y;

	FCanvasTileItem tileItem(FVector2D(x, y), FVector2D(barWidth, barHeight), FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
	tileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(tileItem);
	/* Background tile */

	// Draw the health indicator
	/* Health tile */
	barWidth -= 2.f;
	barHeight -= 2.f;  

	x = center2D.X - barWidth * 0.5f;
	y = center2D.Y + 1.f;

	tileItem.Position = FVector2D(x, y);
	tileItem.SetColor(FLinearColor(0.1f, 1.0f, 0.1f, 1.f));
	tileItem.Size = FVector2D(barWidth * healthPercentage, barHeight);
	Canvas->DrawItem(tileItem);
}

