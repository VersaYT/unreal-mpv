using UnrealBuildTool;
using System;
using System.IO;

    public class UnrealMpvLib : ModuleRules
    {
        public UnrealMpvLib(ReadOnlyTargetRules Target) : base(Target)
        {
        Type = ModuleType.External;

        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../../Dependencies/mpv/build", "libmpv.lib"));

        PublicDelayLoadDLLs.Add("libmpv-2.dll");

        RuntimeDependencies.Add(Path.Combine(PluginDirectory, "Binaries/Win64/libmpv-2.dll"));
        //RuntimeDependencies.Add(Path.Combine("$(PluginDir)/Binaries/ThirdParty/UnrealMpvLib/Win64/" + "libmpv-2.dll"));
        //RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Binaries/Win64/libmpv-2.dll"));

        //PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../../Dependencies/mpv/libmpv"));
        //PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, "../../Dependencies/mpv/libmpv"))



    }
    }