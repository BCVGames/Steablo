// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SteabloCPP : ModuleRules
{
	public SteabloCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
