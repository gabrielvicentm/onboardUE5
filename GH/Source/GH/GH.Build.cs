// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GH : ModuleRules
{
	public GH(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GH",
			"GH/Variant_Platforming",
			"GH/Variant_Platforming/Animation",
			"GH/Variant_Combat",
			"GH/Variant_Combat/AI",
			"GH/Variant_Combat/Animation",
			"GH/Variant_Combat/Gameplay",
			"GH/Variant_Combat/Interfaces",
			"GH/Variant_Combat/UI",
			"GH/Variant_SideScrolling",
			"GH/Variant_SideScrolling/AI",
			"GH/Variant_SideScrolling/Gameplay",
			"GH/Variant_SideScrolling/Interfaces",
			"GH/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
