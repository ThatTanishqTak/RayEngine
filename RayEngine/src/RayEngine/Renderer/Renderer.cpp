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

        m_Camera.position = { 10.0f, 10.0f, 10.0f };
        m_Camera.target = { 0.0f, 0.0f, 0.0f };
        m_Camera.up = { 0.0f, 1.0f, 0.0f };
        m_Camera.fovy = 45.0f;
        m_Camera.projection = CAMERA_PERSPECTIVE;

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

    void Renderer::BeginScene()
    {
        BeginMode3D(m_Camera);
    }

    void Renderer::EndScene()
    {
        DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLACK);
        EndMode3D();
    }
}