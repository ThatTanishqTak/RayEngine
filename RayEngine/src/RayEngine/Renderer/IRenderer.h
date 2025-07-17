#pragma once

namespace RayEngine
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual void BeginScene() = 0;
        virtual void EndScene() = 0;
    };
}