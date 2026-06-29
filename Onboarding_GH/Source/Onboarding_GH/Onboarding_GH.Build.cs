// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Onboarding_GH : ModuleRules
{
	public Onboarding_GH(ReadOnlyTargetRules Target) : base(Target)
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
			"Onboarding_GH",
			"Onboarding_GH/Variant_Platforming",
			"Onboarding_GH/Variant_Platforming/Animation",
			"Onboarding_GH/Variant_Combat",
			"Onboarding_GH/Variant_Combat/AI",
			"Onboarding_GH/Variant_Combat/Animation",
			"Onboarding_GH/Variant_Combat/Gameplay",
			"Onboarding_GH/Variant_Combat/Interfaces",
			"Onboarding_GH/Variant_Combat/UI",
			"Onboarding_GH/Variant_SideScrolling",
			"Onboarding_GH/Variant_SideScrolling/AI",
			"Onboarding_GH/Variant_SideScrolling/Gameplay",
			"Onboarding_GH/Variant_SideScrolling/Interfaces",
			"Onboarding_GH/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
