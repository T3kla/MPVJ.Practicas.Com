// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Com_07 : ModuleRules
{
    public Com_07(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
