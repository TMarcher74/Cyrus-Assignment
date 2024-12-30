// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CyrusAssignment : ModuleRules
{
	public CyrusAssignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"Json", 
			"JsonUtilities",
			"HTTP"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
