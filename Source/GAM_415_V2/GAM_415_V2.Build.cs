// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM_415_V2 : ModuleRules
{
	public GAM_415_V2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
