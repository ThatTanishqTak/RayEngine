#pragma once

#include "RayEngine/Renderer/IRenderer.h"
#include <raylib.h>

namespace RayEngine
{
    class Renderer : public IRenderer
    {
    public:
        Renderer() = default;
        ~Renderer() override = default;

        bool Initialize() override;
        void Shutdown() override;

        void BeginFrame() override;
        void EndFrame() override;

        void BeginScene() override;
        void EndScene() override;

    private:
        Camera3D m_Camera{};
        float m_Rotation = 0.0f;
    };
}