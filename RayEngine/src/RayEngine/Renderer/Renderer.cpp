#include "raypch.h"

#include "RayEngine/Renderer/Renderer.h"
#include "RayEngine/Utilities/Utilities.h"

#include <raylib.h>

namespace RayEngine
{
    bool Renderer::Initialize()
    {
        if (!IsWindowReady())
        {
            RAY_CORE_ERROR("Renderer initialization failed: window is not ready");

            return false;
        }

        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);

        RenderTexture2D checkBuffer = LoadRenderTexture(1, 1);
        if (checkBuffer.id == 0)
        {
            RAY_CORE_ERROR("Failed to create render texture");

            return false;
        }

        UnloadRenderTexture(checkBuffer);

        return true;
    }

    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginFrame()
    {
        BeginDrawing();
        ClearBackground(BLACK);
    }

    void Renderer::EndFrame()
    {
        EndDrawing();
    }
}