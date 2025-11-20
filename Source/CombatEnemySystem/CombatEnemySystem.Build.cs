// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CombatEnemySystem : ModuleRules
{
	public CombatEnemySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		OptimizeCode = CodeOptimization.Never;
			
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "GameplayTags", "AIModule", "StateTreeModule",
				"GameplayStateTreeModule", "NavigationSystem", "MotionWarping", "PropertyBindingUtils", "UMG"
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"SlateCore",
				"GameplayAbilities",
				"ModularGameplay"
			}
			);
		
	}
}
