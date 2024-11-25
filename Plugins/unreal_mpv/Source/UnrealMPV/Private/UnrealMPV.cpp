#include "UnrealMPV.h"
THIRD_PARTY_INCLUDES_START
extern "C" {
#include "client.h"
#include "render.h"
#include "render_gl.h"
}
THIRD_PARTY_INCLUDES_END


class UnrealMPV : public FUnrealMPVModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	mpv_render_context* mpv_gl = nullptr;
};

IMPLEMENT_MODULE(UnrealMPV, UnrealMPV);

void UnrealMPV::StartupModule()
{
	mpv_handle* mpv = mpv_create();
	if (!mpv) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create mpv context"));
	}

	// Initialize with OpenGL rendering
	if (mpv_render_context_create(&mpv_gl, mpv, nullptr) < 0) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create render context"));
		mpv_destroy(mpv);
	}

	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void UnrealMPV::ShutdownModule()
{

	mpv_render_context_free(mpv_gl);
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}