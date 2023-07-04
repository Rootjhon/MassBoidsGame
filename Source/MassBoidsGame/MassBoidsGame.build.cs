// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MassBoidsGame : ModuleRules
{
    public MassBoidsGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                "MassBoidsGame"
            });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        PrivateDependencyModuleNames.AddRange(
    new string[] {
                "MassEntity",
                "StructUtils",
                "MassCommon",
                "MassMovement",
                "MassActors",
                "MassSpawner",
                "MassGameplayDebug",
                "MassSignals",
                "MassCrowd",
                "MassActors",
                "MassSpawner",
                "MassRepresentation",
                "MassReplication",
                "MassNavigation",
    }
);
    }
}
