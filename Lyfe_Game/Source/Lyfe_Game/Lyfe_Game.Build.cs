// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Lyfe_Game : ModuleRules
{
	//include ThirdParty content 
	//private string ModulePath
 //   {
 //       get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
 //   }

    //private string ThirdPartyPath
    //{
    //    get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    //}
	
	public Lyfe_Game(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "UMG", "ProceduralMeshComponent" });

		//PrivateDependencyModuleNames.AddRange(new string[] { "CustomMeshComponent" });

        //PrivateIncludePathModuleNames.AddRange(new string[] { "CustomMeshComponent" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
