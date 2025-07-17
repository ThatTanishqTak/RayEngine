#pragma once

// Core header for the Application class controlling window and rendering.
#include "RayEngine/Window/Window.h"
#include "RayEngine/Renderer/Renderer.h"

#include <memory>

namespace RayEngine
{
    // Encapsulates raw command line arguments.
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;
    };

    // Holds settings required to create an application instance.
    struct ApplicationSpecification
    {
        const char* Name = "RayEngine-Application";
        int Width = 800;
        int Height = 600;
        bool VSync = false;
        ApplicationCommandLineArgs CommandLineArgs;
    };

    // Main application entry point.
    class Application
    {
    public:
        Application() = default;
        explicit Application(const ApplicationSpecification& specification);
        virtual ~Application();

        // Starts the application loop.
        virtual void Run()
        {
            while (!m_Window->ShouldClose())
            {
                m_Window->PollEvents();

                if (m_Renderer)
                {
                    m_Renderer->BeginFrame();

                    m_Renderer->BeginScene();
                    m_Renderer->EndScene();

                    m_Renderer->EndFrame();
                }
            }
        }

    protected:
        ApplicationSpecification m_Specification{};

        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };
}