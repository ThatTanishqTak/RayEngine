#include "raypch.h"

#include "RayEngine/Core/Application.h"

namespace RayEngine
{
	Application::Application(const ApplicationSpecification& specification) : m_Specification(specification)
	{
		m_Window = std::make_unique<Window>(WindowSpecification{ m_Specification.Name, m_Specification.Width, m_Specification.Height, m_Specification.VSync });
		if (!m_Window->Initialize())
		{
			std::cout << "Window's fucked";
		}

		m_Renderer = std::make_unique<Renderer>();
		if (!m_Renderer)
		{
			std::cout << "Renderer's fucked";
		}
	}

	Application::~Application()
	{
		if (m_Window)
		{
			m_Window->Shutdown();
		}
	}
}