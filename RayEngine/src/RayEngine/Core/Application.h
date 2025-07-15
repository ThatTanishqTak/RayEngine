#pragma once

#include "RayEngine/Window/Window.h"

#include <raylib.h>
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

                BeginDrawing();
                //BeginMode3D();
                ClearBackground(BLACK);

                //EndMode3D();
                EndDrawing();
            }
        }

    protected:
        ApplicationSpecification m_Specification;

        std::unique_ptr<Window> m_Window;
    };
}