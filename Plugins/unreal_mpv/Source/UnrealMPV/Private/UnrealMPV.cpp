#include "UnrealMpv.h"
THIRD_PARTY_INCLUDES_START
extern "C" {
#include "client.h"
#include "render.h"
#include "render_gl.h"
}
THIRD_PARTY_INCLUDES_END

#include "Misc/Paths.h"


class UnrealMpv : public FUnrealMpvModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	mpv_render_context* mpv_gl = nullptr;
};

IMPLEMENT_MODULE(UnrealMpv, UnrealMpv);

void UnrealMpv::StartupModule()
{
	const FString DLLs[] = {
		"libiconv-2.dll",
		"libfribidi-0.dll",
		"zlib1.dll",
		"libbz2-1.dll",
		"libpng16-16.dll",
		"libbrotlicommon.dll",
		"libbrotlidec.dll",
		"libglib-2.0-0.dll",
		"libintl-8.dll",
		"libc++.dll",
		"libgraphite2.dll",
		"USP10.dll",
		"libfreetype-6.dll",
		"libharfbuzz-0.dll",
		"libunibreak-6.dll",
		"libfontconfig-1.dll",
		"libass-9.dll",
		"avcodec-60.dll",
		"avfilter-9.dll",
		"avformat-60.dll",
		"avutil-58.dll",
		"libplacebo-349.dll",
		"swresample-4.dll",
		"swscale-7.dll",
		"AVRT.dll",
		"liblcms2-2.dll",
		"avdevice-60.dll",
		"libbluray-2.dll",
		"lua51.dll",
		"libzimg-2.dll",
		"libcaca-0.dll",
		"libjpeg-8.dll",
		"libshaderc_shared.dll",
		"libspirv-cross-c-shared.dll",
		"vulkan-1.dll",
		"libva_win32.dll",
		"libva.dll",
		"libmpv-2.dll"
	};

	FString UMBinDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("unreal_mpv"), TEXT("Binaries"), TEXT("ThirdParty"), TEXT("UnrealMpvLib"), TEXT("Win64"), TEXT("/"));

	for (const FString& DLL : DLLs)
	{
		FString Where = UMBinDir + DLL;
		void* Handle = FPlatformProcess::GetDllHandle(*Where);
		if (!Handle)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to open %s"), *Where);
		}
	}

	mpv_handle* mpv = mpv_create();
	if (!mpv) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create mpv context"));
	}

	// Initialize with OpenGL rendering
	if (mpv_render_context_create(&mpv_gl, mpv, nullptr) < 0) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create render context"));
		mpv_destroy(mpv);
	}

	UE_LOG(LogTemp, Warning, TEXT("test"));
	UE_LOG(LogTemp, Warning, TEXT("test"));
	UE_LOG(LogTemp, Warning, TEXT("test"));

	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void UnrealMpv::ShutdownModule()
{

	mpv_render_context_free(mpv_gl);
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}