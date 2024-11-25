using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class UnrealMPV : ModuleRules
    {
        public UnrealMPV(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../Dependencies/mpv/libmpv"));
            PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, "../../Dependencies/mpv/libmpv"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../Dependencies/mpv/build/libmpv.a"));

            PublicIncludePaths.AddRange(
                new string[] {
					// ... add public include paths required here ...
				}
                );

            PrivateIncludePaths.AddRange(
                new string[] {
					// ... add other private include paths required here ...
				}
                );

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core","CoreUObject", "Engine"
					// ... add other public dependencies that you statically link with here ...
				}
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
					// ... add private dependencies that you statically link with here ...
				}
                );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
					// ... add any modules that your module loads dynamically here ...
				}
                );
        }
    }
}