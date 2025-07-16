#pragma once

#include "RayEngine/Window/EngineWindow.h"
#include "RayEngine/Renderer/Renderer.h"

#include <memory>

namespace RayEngine
{
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;
    };

    struct ApplicationSpecification
    {
        const char* Name = "RayEngine-Application";
        int Width = 800;
        int Height = 600;
        bool VSync = false;
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application
    {
    public:
        Application() = default;
        Application(const ApplicationSpecification& specification);
        virtual ~Application();

        virtual void Run()
        {
            while (!m_Window->ShouldClose())
            {
                m_Window->PollEvents();

                if (m_Renderer)
                {
                    m_Renderer->BeginFrame();
                    m_Renderer->EndFrame();
                }
            }
        }

    protected:
        ApplicationSpecification m_Specification;

        std::unique_ptr<EngineWindow> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };
}