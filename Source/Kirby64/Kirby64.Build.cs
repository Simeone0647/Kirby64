// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Kirby64 : ModuleRules
{
	public Kirby64(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara" });
	}
}
