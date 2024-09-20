// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CombatEnemySystem : ModuleRules
{
	public CombatEnemySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "AIModule"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				
				"Slate",
				"SlateCore",
				"StateTreeModule",
				"GameplayStateTreeModule",
				"GameplayAbilities",
				"ModularGameplay"
			}
			);
		
	}
}
