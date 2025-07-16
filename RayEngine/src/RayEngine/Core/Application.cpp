#include "raypch.h"

#include "RayEngine/Core/Application.h"
#include "RayEngine/Utilities/Utilities.h"

namespace RayEngine
{
    // Construct application and prepare window and renderer.
    Application::Application(const ApplicationSpecification& specification) : m_Specification(specification)
    {
        m_Window = std::make_unique<EngineWindow>(WindowSpecification{ m_Specification.Name, m_Specification.Width, m_Specification.Height, m_Specification.VSync });
        if (!m_Window->Initialize())
        {
            RAY_CORE_ERROR("Failed to initialize window");
        }

        m_Renderer = std::make_unique<Renderer>();
        if (!m_Renderer)
        {
            RAY_CORE_ERROR("Failed to create renderer");
        }
    }

    Application::~Application()
    {
        if (m_Window)
        {
            m_Window->Shutdown();
            m_Window.reset();
        }
     
        if (m_Renderer)
        {
            m_Renderer->Shutdown();
            m_Renderer.reset();
        }
    }

    void Application::Run()
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
}