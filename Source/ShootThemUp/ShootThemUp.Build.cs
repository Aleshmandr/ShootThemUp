using UnrealBuildTool;

public class ShootThemUp : ModuleRules
{
	public ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"NavigationSystem",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PrivateIncludePaths.AddRange(new[]
		{
			"ShootThemUp/Public/Player",
			"ShootThemUp/Public/Components",
			"ShootThemUp/Public/Weapon",
			"ShootThemUp/Public/UI",
			"ShootThemUp/Public/Animations",
			"ShootThemUp/Public/Pickups",
			"ShootThemUp/Public/Dev",
			"ShootThemUp/Public/AI",
			"ShootThemUp/Public/AI/Tasks",
			"ShootThemUp/Public/AI/Services",
			"ShootThemUp/Public/AI/Decorators",
			"ShootThemUp/Public/AI/EQS",
			"ShootThemUp/Public/Weapon/Components",
			"ShootThemUp/Public/Menu",
			"ShootThemUp/Public/Menu/UI",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}