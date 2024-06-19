// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;
public class SuisdkUnreal : ModuleRules
{
	public SuisdkUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//bEnableExceptions = true;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			string unreal_sui_sdk_LibPath = Path.Combine(ModuleDirectory,"../../", "libsui_rust_sdk.dylib");
			string destinationDirectory = Target.ProjectFile.Directory.FullName;
			// File.Copy(unreal_sui_sdk_LibPath, Path.Combine(destinationDirectory, "libsui_rust_sdk.dylib"), true);
			// PublicAdditionalLibraries.Add(Path.Combine(destinationDirectory, "libsui_rust_sdk.dylib"));
			PublicAdditionalLibraries.Add(unreal_sui_sdk_LibPath);
			PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "../../") });
			PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "../../../") });
		}
		//bEnableUndefinedIdentifierWarnings = false;
		CppStandard = CppStandardVersion.Cpp17;
	}
}
