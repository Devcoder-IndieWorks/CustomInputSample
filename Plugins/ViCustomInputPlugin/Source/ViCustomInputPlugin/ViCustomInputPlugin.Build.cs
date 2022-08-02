// Copyright Devcoder. All Rights Reserved.
using UnrealBuildTool;

public class ViCustomInputPlugin : ModuleRules
{
	public ViCustomInputPlugin( ReadOnlyTargetRules Target ) : base( Target )
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = false;
		bLegacyPublicIncludePaths = false;
		CppStandard = CppStandardVersion.Cpp17;
		PrivatePCHHeaderFile = "Private/ViCustomInputPluginPCH.h";
		
		PrivateIncludePaths.AddRange(
		    new string[] {
				"ViCustomInputPlugin/Private"
			} );
		
		// Unreal Engine Module
		PrivateDependencyModuleNames.AddRange(
		    new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
                "Slate",
                "SlateCore"
			} );
	}
}