// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LudumeDare48 : ModuleRules
{
	public LudumeDare48(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "NavigationSystem", "MediaAssets", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { "LudumeDare48", "LudumeDare48/Public", "LudumeDare48/Public/AI", "LudumeDare48/Public/Items", "LudumeDare48/Public/HUD", "LudumeDare48/Public/Components", "LudumeDare48/Menu", "LudumeDare48/Menu/Public", "LudumeDare48/Menu/Public/HUD", "LudumeDare48/Menu/Public/HUD/UI" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
