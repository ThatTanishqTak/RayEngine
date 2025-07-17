#include "raypch.h"

#include "RayEngine/Renderer/RaylibRenderer.h"
#include "RayEngine/Utilities/Utilities.h"

#include <raylib.h>

namespace RayEngine
{
    bool RaylibRenderer::Initialize()
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

    void RaylibRenderer::Shutdown()
    {

    }

    void RaylibRenderer::BeginFrame()
    {
        BeginDrawing();
        ClearBackground(BLACK);
    }

    void RaylibRenderer::EndFrame()
    {
        EndDrawing();
    }
}