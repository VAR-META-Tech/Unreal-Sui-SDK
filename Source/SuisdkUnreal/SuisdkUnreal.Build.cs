// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;
public class SuisdkUnreal : ModuleRules
{
	public SuisdkUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Json", "JsonUtilities", "HTTP", "ImageWrapper" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			string unreal_sui_sdk_LibPath = Path.Combine(ModuleDirectory, "../../Lib/", "libsui_rust_sdk.dylib");
			string destinationDirectory = Target.ProjectFile.Directory.FullName;
			PublicAdditionalLibraries.Add(unreal_sui_sdk_LibPath);
			PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "../../Lib/") });
			PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "../../../") });
		}
		CppStandard = CppStandardVersion.Cpp17;
	}
}
