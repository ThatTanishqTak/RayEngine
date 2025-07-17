#pragma once

#include "RayEngine/Renderer/IRenderer.h"

namespace RayEngine
{
    class RaylibRenderer : public IRenderer
    {
    public:
        RaylibRenderer() = default;
        ~RaylibRenderer() override = default;

        bool Initialize() override;
        void Shutdown() override;

        void BeginFrame() override;
        void EndFrame() override;

    private:

    };
}