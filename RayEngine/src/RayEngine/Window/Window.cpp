#include "raypch.h"

#include "RayEngine/Window/Window.h"


namespace RayEngine
{
	Window::Window(const WindowSpecification& specification) : m_Specification(specification)
	{

	}


	bool Window::Initialize()
	{
		InitWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title);
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		SetVSync(m_Specification.VSync);
		m_Window = GetWindowHandle();

		if (!IsWindowReady())
		{
			return false;
		}

		SetTargetFPS(60);
		
		return true;
	}

	void Window::Shutdown()
	{
		if (IsWindowReady())
		{
			CloseWindow();
		}
	}

	bool Window::ShouldClose() const
	{
		return WindowShouldClose();
	}

	void Window::PollEvents()
	{
		PollInputEvents();
	}

	void Window::SetVSync(bool enabled)
	{
		m_Specification.VSync = enabled;
		if (enabled)
		{
			SetTargetFPS(60);
		}

		else
		{
			SetTargetFPS(0);
		}
	}

	void Window::SetTitle(const char* title)
	{
		m_Specification.Title = title;
		SetWindowTitle(title);
	}
}