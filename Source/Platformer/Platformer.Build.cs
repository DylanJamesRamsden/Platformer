// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Platformer : ModuleRules
{
	public Platformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// Public vs Private Dependancies
		// - Public: Modules that depend on our module will also depend on the dependencies defined in public
		// - Private: Any module that depends on our module won't depend on the dependencies defined in private

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags"});
		
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities" });
		
	}
}
