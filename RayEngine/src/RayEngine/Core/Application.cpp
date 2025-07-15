#include "raypch.h"

#include "RayEngine/Core/Application.h"

namespace RayEngine
{
	Application::Application(const ApplicationSpecification& specification) : m_Specification(specification)
	{
		m_Window = std::make_unique<Window>(WindowSpecification{ m_Specification.Name, m_Specification.Width, m_Specification.Height });
		if (!m_Window->Initialize())
		{
			std::cout << "Window's fucked";
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